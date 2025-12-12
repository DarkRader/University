"""
This module defines class DiscussionService that work with Discussion
"""
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractDiscussionService
from sqlalchemy.orm import Session
import logging

log = logging.getLogger(__name__)


class DiscussionService(AbstractDiscussionService):
    """
    Class DiscussionService represent service that work with Discussion
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_permission_crud = crud.DocumentPermission(db)
        self.document_crud = crud.Document(db)
        super().__init__(crud.Discussion(db))

    def get_discussion(self, uuid: UUID, user: models.User) -> models.Discussion | None:
        log.info(f"Retrieving discussion with UUID: {uuid}")
        # control permissions
        discussion = self.crud.get(uuid)
        if discussion is None:
            log.warning(f"Discussion not found for UUID: {uuid}")
            return None

        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            discussion.document_uuid, user.uuid)

        if permission is None:
            log.warning(f"Unauthorized access to discussion with UUID: {uuid}, by user {user.username}")
            return None

        return discussion

    def create_discussion(self, discussion: schemas.DiscussionCreate,
                          user: schemas.User) \
            -> models.Discussion | None:
        log.info("Attempting to create a new discussion")
        # Check for valid discussion creation conditions
        if (discussion.crosslink is None and discussion.evaluation_uuid is None) or \
                (discussion.crosslink is not None and discussion.evaluation_uuid is not None):
            return None

        # control permissions
        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            discussion.document_uuid, user.uuid)

        if permission is None:
            log.warning(f"Unauthorized attempt to create discussion for document UUID: {discussion.document_uuid}, by user {user.username}")
            return None

        created_discussion = self.crud.create(obj_in=discussion)
        log.info(f"Discussion created with UUID: {created_discussion.uuid}")
        return created_discussion

    def update_discussion(self, uuid: UUID,
                          obj_in: schemas.DiscussionUpdate,
                          user: schemas.User) -> \
            models.Discussion | None:
        log.info(f"Updating discussion with UUID: {uuid}")
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            log.warning(f"Discussion update failed: No discussion found with UUID: {uuid}")
            return None

        # control permissions
        discussion = self.crud.get(uuid)
        permission = self.document_permission_crud.\
            get_by_document_uuid_user_uuid_and_permission_type(
                discussion.document_uuid, user.uuid, models.DocumentPermissionType.SUBMITTER)

        if permission is None:
            log.warning(f"Unauthorized attempt to update discussion with UUID: {uuid}, by user {user.username}")
            return None

        discussion_update = schemas.utils.as_dict(obj_in)
        if obj_in.state == models.DiscussionState.RESOLVED:
            discussion_update["resolved_at"] = datetime.utcnow()
        updated_discussion = self.crud.update(db_obj=obj_to_update, obj_in=discussion_update)
        log.info(f"Discussion updated with UUID: {updated_discussion.uuid}")
        return updated_discussion

    def get_by_document_uuid_all(self, document_uuid: UUID,
                                 user: schemas.User) -> list[Type[models.Discussion]] | None:
        log.info(f"Fetching all discussions for document UUID: {document_uuid}")
        # control permissions
        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            document_uuid, user.uuid)

        if permission is None:
            log.info(f"User {user.username} does not have permission to view discussions for document UUID: {document_uuid}")
            return None

        return self.crud.get_by_document_uuid_all(document_uuid)

    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[models.Discussion]]:
        log.info(f"Fetching discussions for document UUID: {document_uuid} with skip: {skip} and limit: {limit}")
        return self.crud.get_by_document_uuid_multi(document_uuid, skip, limit)

    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.DiscussionState) \
            -> list[Type[models.Discussion]]:
        log.info(f"Fetching discussions for document UUID: {document_uuid} and state: {state}")
        return self.crud.get_by_document_uuid_and_state_all(document_uuid, state)
