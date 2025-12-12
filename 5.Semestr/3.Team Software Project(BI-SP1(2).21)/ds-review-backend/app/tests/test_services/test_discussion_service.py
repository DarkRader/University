"""
Module for testing comment service
"""
from uuid import uuid4
from services import DiscussionService, UserService

import pytest
import models
import schemas
from ..utils import as_dict
from .test_user_create import user_create1, user_create2, user_create3, user_create4, \
    user_create5, user_create6, user_create7, user_create8


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture()
def service_discussion(db_session) -> DiscussionService:
    """Return CommentService."""
    return DiscussionService(db=db_session)


@pytest.fixture()
def service_user(db_session) -> UserService:
    """Return UserService."""
    return UserService(db=db_session)


def document_permission_create(document_uuid, user_uuid, permission_type) -> \
        schemas.DocumentPermissionCreate:
    """Return create_schema_data for document."""
    return schemas.DocumentPermissionCreate(
        permission_type=permission_type,
        document_uuid=document_uuid,
        user_uuid=user_uuid
    )


@pytest.fixture(scope="module")
def discussion_update() -> schemas.DiscussionUpdate:
    """Return update_schema_data for comment."""
    return schemas.DiscussionUpdate(
        state=models.DiscussionState.RESOLVED
    )


@pytest.fixture
def document_create() -> schemas.DocumentCreate:
    """Return document_create for document."""
    return schemas.DocumentCreate(
        title="title",
        doc_type=models.DocumentType.HTML,
        content="Test content"
    )


@pytest.fixture
def discussion_create() -> schemas.DiscussionCreate:
    """Return discussion_create for discussion."""
    test_crosslink = schemas.Crosslink(
        start_index=0,
        end_index=1,
        element_ids=[]
    )

    return schemas.DiscussionCreate(
        crosslink=test_crosslink,
        document_uuid=uuid4()
    )


def create_discussion(service_discussion,
                      document_create,
                      discussion_create,
                      permission_type,
                      user) -> models.Discussion:
    """
    Additional function for creating a discussion
    """
    doc_in_db = service_discussion.document_crud.create(document_create)
    service_discussion.document_permission_crud.create(
        document_permission_create(doc_in_db.uuid, user.uuid, permission_type))
    discussion_create.document_uuid = doc_in_db.uuid
    discussion_in_db = service_discussion.create_discussion(discussion_create, user)
    assert discussion_in_db is not None
    assert discussion_in_db.document is not None
    assert discussion_in_db.document_uuid is not None
    return discussion_in_db


def test_create(service_discussion,
                document_create,
                discussion_create,
                service_user):
    """
    Test for create method in DiscussionService
    """
    user = service_user.create(obj_in=user_create1())
    create_discussion(service_discussion,
                      document_create,
                      discussion_create,
                      models.DocumentPermissionType.REVIEWER,
                      user)


def test_create_with_none_crosslink_and_evaluation(service_discussion,
                                                   document_create,
                                                   discussion_create,
                                                   service_user):
    """
    Test for create method in DiscussionService
    """
    discussion_create.crosslink = None
    discussion_create.evaluation_uuid = None
    doc_in_db = service_discussion.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    user = service_user.create(obj_in=user_create2())
    discussion_in_db = service_discussion.create_discussion(discussion_create, user)
    assert discussion_in_db is None


def test_create_with_not_none_crosslink_and_evaluation(service_discussion,
                                                       document_create,
                                                       discussion_create,
                                                       service_user):
    """
    Test for create method in DiscussionService
    """
    discussion_create.evaluation_uuid = uuid4()
    doc_in_db = service_discussion.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    user = service_user.create(obj_in=user_create3())
    discussion_in_db = service_discussion.create_discussion(discussion_create, user)
    assert discussion_in_db is None


def test_get_created_discussion(service_discussion,
                                document_create,
                                discussion_create,
                                service_user):
    """
    Test for get method in DiscussionService
    """
    user = service_user.create(obj_in=user_create4())
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create,
                                         models.DocumentPermissionType.REVIEWER,
                                         user)

    db_obj = service_discussion.get(discussion_in_db.uuid)
    assert db_obj is not None


def test_delete_created_discussion(service_discussion,
                                   document_create,
                                   discussion_create,
                                   service_user):
    """
    Test for remove method in DiscussionService
    """
    user = service_user.create(obj_in=user_create5())
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create,
                                         models.DocumentPermissionType.REVIEWER,
                                         user)

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert discussion_in_db == db_obj_removed


def test_delete_nonexistent_discussion(service_discussion,
                                       document_create,
                                       discussion_create,
                                       service_user):
    """
    Test for remove method in DiscussionService
    for nonexistent discussion
    """
    user = service_user.create(obj_in=user_create6())
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create,
                                         models.DocumentPermissionType.REVIEWER,
                                         user)

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert db_obj_removed is not None

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert db_obj_removed is None

    db_obj_removed = service_discussion.remove(None)
    assert db_obj_removed is None


def test_update(service_discussion,
                document_create,
                discussion_create,
                discussion_update,
                service_user):
    """
    Test for update method in DiscussionService
    """
    user = service_user.create(obj_in=user_create7())
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create,
                                         models.DocumentPermissionType.SUBMITTER,
                                         user)

    db_obj_to_update = service_discussion.get(discussion_in_db.uuid)
    db_obj_updated = service_discussion.update_discussion(db_obj_to_update.uuid,
                                                          discussion_update, user)

    # only for testing
    discussion_update.crosslink = db_obj_updated.crosslink

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in discussion_update:
        assert db_obj_updated_data[field] == value
    for field, value in discussion_create:
        if field not in discussion_update.dict():
            assert db_obj_updated_data[field] == value


def test_get_by_document_uuid_all(service_discussion,
                                  document_create,
                                  discussion_create,
                                  service_user):
    """
    Test for get_by_document_uuid_all method in DiscussionService
    """
    doc_in_db = service_discussion.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid

    user = service_user.create(obj_in=user_create8())
    nr_of_discussion = 3
    discussions = []
    for _ in range(nr_of_discussion):
        service_discussion.document_permission_crud.create(
            document_permission_create(doc_in_db.uuid, user.uuid,
                                       models.DocumentPermissionType.REVIEWER))
        discussions.append(service_discussion.create_discussion(discussion_create, user))
    assert doc_in_db is not None
    assert doc_in_db.discussions != []

    discussion_list = service_discussion.get_by_document_uuid_all(doc_in_db.uuid, user)
    assert len(discussion_list) == nr_of_discussion
    for diss_id, discussion in enumerate(discussion_list):
        assert discussion == discussions[diss_id]
