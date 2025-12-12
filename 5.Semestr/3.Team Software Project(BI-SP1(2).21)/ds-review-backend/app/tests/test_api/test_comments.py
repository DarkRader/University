"""Module for comments api integration tests."""
from uuid import uuid4

import pytest
from api.comments import router as comments_router
import schemas
from .test_discussions import get_discussion, create_comment_and_discussion

# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture(scope="module")
def crosslink():
    """Crosslink schema."""
    return schemas.Crosslink(
        start_index=5,
        end_index=7,
        element_ids=["1,2,3"]
    )


@pytest.fixture(scope="module")
def discussion_create_schema(crosslink):
    """Discussion create schema."""
    return schemas.DiscussionCreate(
        document_uuid=uuid4(),
        crosslink=crosslink
    )


@pytest.fixture(scope="module")
def comment_create_schema():
    """Comment create schema of first comment in discussion."""
    return schemas.CommentCreate(
        content="My first comment."
    )


@pytest.fixture(scope="module")
def comment_and_discussion_create_schema(comment_create_schema, discussion_create_schema):
    """CommentAndDiscussion create schema."""
    return schemas.CommentAndDiscussionCreate(
        comment=comment_create_schema,
        discussion=discussion_create_schema
    )


@pytest.fixture(scope="module")
def comment_and_discussion_create_add_comment_schema():
    """CommentAndDiscussionCreate schema to add to existing discussion."""
    return schemas.CommentAndDiscussionCreate(
        comment=schemas.CommentCreate(
            content="My not first comment.",
            discussion_uuid=uuid4(),
            replied_comment_uuid=None,
        ),
        discussion=None
    )


@pytest.fixture(scope="module")
def comment_update_schema():
    """CommentUpdate schema."""
    return schemas.CommentUpdate(
        content="Updated comment content:)"
    )


def test_create_comment_and_discussion_add_comment_and_update_comment(
        client, comment_and_discussion_create_schema,
        comment_and_discussion_create_add_comment_schema,
        comment_update_schema, user
):
    """Test create comment and discussion, add comment and update comment."""
    _, comment = create_comment_and_discussion(client, comment_and_discussion_create_schema, user)
    assert comment is not None
    comment_and_discussion_create_add_comment_schema.comment.discussion_uuid = \
        comment.discussion_uuid
    response_create = client.post(
        comments_router.prefix,
        headers=user.auth_header,
        content=comment_and_discussion_create_add_comment_schema.json(exclude_unset=True)
    )
    assert response_create.status_code == 201
    comment_parent = schemas.Comment(**response_create.json())
    discussion = get_discussion(client, comment_parent.discussion_uuid, user.auth_header)
    assert discussion is not None
    assert len(discussion.comments) == 2
    response_update = client.put(
        f"{comments_router.prefix}/{comment_parent.uuid}",
        headers=user.auth_header,
        json=comment_update_schema.dict()
    )
    assert response_update.status_code == 200
    comment_updated = schemas.Comment(**response_update.json())
    assert comment_updated.uuid == comment_parent.uuid
    assert comment_updated.content == comment_update_schema.content


def test_add_child_comment(
        client, comment_and_discussion_create_schema,
        comment_and_discussion_create_add_comment_schema,
        user
):
    """Test create comment and discussion, add comment and update comment."""
    # create discussion and comment - get the comment
    _, comment = create_comment_and_discussion(client, comment_and_discussion_create_schema, user)
    assert comment is not None

    # create another comment in the discussion
    comment_and_discussion_create_add_comment_schema.comment.discussion_uuid = \
        comment.discussion_uuid
    response_create_parent = client.post(
        comments_router.prefix,
        headers=user.auth_header,
        content=comment_and_discussion_create_add_comment_schema.json(exclude_unset=True)
    )
    assert response_create_parent.status_code == 201
    comment_parent = schemas.Comment(**response_create_parent.json())
    discussion = get_discussion(client, comment_parent.discussion_uuid, user.auth_header)
    assert discussion is not None
    assert len(discussion.comments) == 2

    # create a child comment, having the above comment as a parent
    child_comment_create_schema = schemas.CommentAndDiscussionCreate(
        comment=schemas.CommentCreate(
            content="Child comment",
            discussion_uuid=discussion.uuid,
            replied_comment_uuid=comment_parent.uuid
        )
    )
    response_create_child = client.post(
        url=comments_router.prefix,
        headers=user.auth_header,
        content=child_comment_create_schema.json()
    )
    assert response_create_child.status_code == 201
    comment_child = schemas.Comment(**response_create_child.json())
    discussion = get_discussion(client, comment_parent.discussion_uuid, user.auth_header)
    assert discussion is not None
    assert len(discussion.comments) == 3
    assert comment_child.replied_comment_uuid == comment_parent.uuid


def test_child_and_parent_comments_from_different_discussions(
        client, comment_and_discussion_create_schema,
        comment_and_discussion_create_add_comment_schema,
        user
):
    _, comment_1 = create_comment_and_discussion(
        client, comment_and_discussion_create_schema, user
    )
    _, comment_2 = create_comment_and_discussion(
        client, comment_and_discussion_create_schema, user
    )
    assert comment_1 is not None and comment_2 is not None
    # try to create another comment to discussion_1
    # with parent comment from discussion_2
    invalid_child_comment_schema = schemas.CommentAndDiscussionCreate(
        comment=schemas.CommentCreate(
            content="My invalid child comment",
            discussion_uuid=comment_1.discussion_uuid,
            replied_comment_uuid=comment_2.uuid,
        )
    )
    response_create = client.post(
        url=comments_router.prefix,
        headers=user.auth_header,
        content=invalid_child_comment_schema.json()
    )
    assert response_create.status_code == 400
