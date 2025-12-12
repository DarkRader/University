"""
API controllers for comments.
"""
from uuid import UUID
from typing import Any, Annotated

from fastapi import APIRouter, Depends, status, responses, Body, Path

import schemas
from api import utils
from api.user_authenticator import get_current_user
from schemas import User
from services import CommentService

router = APIRouter(
    prefix="/comments",
    tags=[utils.fastapi_docs.COMMENT_TAG["name"]]
)


@router.post("/",
             response_model=schemas.Comment,
             responses={
                 400: {"model": utils.Message, "description": "Couldn't create comment."},
             },
             status_code=status.HTTP_201_CREATED,
             description="""
There are two ways to use this request: Post the first comment in a discussion (and create the discussion) or post a comment in an existing discussion (reply to a comment).

A discussion is a thread of comments. A discussion may be tied to a section of the document or an evaluation.

When posting the first comment, a discussion is also created. The parameters of "comment" "discussion_uuid" and "replied_comment_uudi" are null. The parameters of discussion are: crosslink (to which part of the document is the comment tied), document_uuid of the document and evaluation_uuid (if the comment is tied to an evaluation. If not, it is null)

When posting in an already existing discussion, the "discussion" parameter will be null. Parameters of "comment" will be the discusion_uuid of the discussion this comment is posted to and "replied_comment_uuid" the uuid of a coment in this discussion the posted comment is replying to.
"""
             )
async def post_comment(service: Annotated[CommentService, Depends(CommentService)],
                       user: Annotated[User, Depends(get_current_user)],
                       comment_and_discussion: schemas.CommentAndDiscussionCreate,
                       ) -> Any:
    """
    There are two ways to use this request: Post the first comment in a discussion (and create the discussion) or post a comment in an existing discussion (reply to a comment).

    A discussion is a thread of comments. A discussion may be tied to a section of the document or an evaluation.

    When posting the first comment, a discussion is also created. The parameters of "comment" "discussion_uuid" and "replied_comment_uudi" are null. The parameters of discussion are: crosslink (to which part of the document is the comment tied), document_uuid of the document and evaluation_uuid (if the comment is tied to an evaluation. If not, it is null)

    When posting in an already existing discussion, the "discussion" parameter will be null. Parameters of "comment" will be the discusion_uuid of the discussion this comment is posted to and "replied_comment_uuid" the uuid of a coment in this discussion the posted comment is replying to.

    :param service: Comment service.
    :param user: Current user.
    :param comment_and_discussion: CommentCreate schema and voluntary DiscussionCreate schema.
    """
    comment = service.create_comment(
        comment_and_discussion.comment, comment_and_discussion.discussion, user
    )
    if not comment:
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                "message": "Could not create comment, probably due to invalid "
                           "discussion_uuid or document_uuid. Also make sure, that if "
                           "replied_comment_uuid is present, it is from the same discussion."
            }
        )
    return comment


@router.put("/{comment_uuid}",
            response_model=schemas.Comment,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_comment(service: Annotated[CommentService, Depends(CommentService)],
                         user: Annotated[User, Depends(get_current_user)],
                         comment_uuid: Annotated[UUID, Path()],
                         comment: Annotated[schemas.CommentUpdate, Body()]) -> Any:
    """
    Update comment with uuid equal to comment_uuid.

    :param service: Comment service.
    :param user: Current user.
    :param comment_uuid: id of the comment.
    :param comment: CommentUpdate schema.
    """
    comment = service.update_comment(comment_uuid, comment, user)
    if not comment:
        raise utils.EntityNotFoundException(utils.Entity.COMMENT, comment_uuid)
    return comment
