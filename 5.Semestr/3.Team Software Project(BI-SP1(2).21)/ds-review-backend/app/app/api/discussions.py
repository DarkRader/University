"""
API controllers for discussions.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Query, Path, Body

import schemas
from api import utils
from api.user_authenticator import get_current_user
from schemas import User
from services import DiscussionService

router = APIRouter(
    prefix="/discussions",
    tags=[utils.fastapi_docs.DISCUSSION_TAG["name"]]
)


@router.get("/",
            response_model=List[schemas.Discussion],
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_document_discussions(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        user: Annotated[User, Depends(get_current_user)],
        document_uuid: Annotated[UUID, Query()]
) -> Any:
    """
    Get all discussions containing comments of document with uuid equal to document_uuid.

    :param service: Discussion service.
    :param user: Current user.
    :param document_uuid: uuid of the document.
    """
    discussions = service.get_by_document_uuid_all(document_uuid, user)
    if discussions is None:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return discussions


@router.get("/{discussion_uuid}",
            response_model=schemas.Discussion,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_discussion(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        user: Annotated[User, Depends(get_current_user)],
        discussion_uuid: Annotated[UUID, Path()]
) -> Any:
    """
    Get discussion with uuid equal to discussion_uuid.

    :param service: Discussion service.
    :param user: Current user.
    :param discussion_uuid: uuid of the discussion.
    """
    discussion = service.get_discussion(discussion_uuid, user)
    if not discussion:
        raise utils.EntityNotFoundException(utils.Entity.DISCUSSION, discussion_uuid)
    return discussion


@router.put("/{discussion_uuid}",
            response_model=schemas.Discussion,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_discussion(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        user: Annotated[User, Depends(get_current_user)],
        discussion_uuid: Annotated[UUID, Path()],
        discussion: Annotated[schemas.DiscussionUpdate, Body()]
) -> Any:
    """
    Update discussion with uuid equal to discussion_uuid.

    :param service: Discussion service.
    :param user: Current user.
    :param discussion_uuid: uuid of the discussion.
    :param discussion: Discussion update schema.
    """
    discussion_updated = service.update_discussion(discussion_uuid, discussion, user)
    if not discussion_updated:
        raise utils.EntityNotFoundException(utils.Entity.DISCUSSION, discussion_uuid)
    return discussion_updated
