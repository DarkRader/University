"""
This module defines class DiscussionService that work with Discussion
"""
import logging
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends
from sqlalchemy.orm import Session
from db import get_db
import crud
import schemas

import models.document

from services import AbstractCommentService

log = logging.getLogger(__name__)


class CommentService(AbstractCommentService):
    """
    Class CommentService represent service that work with Comment
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_permission_crud = crud.DocumentPermission(db)
        self.document_crud = crud.Document(db)
        self.discussion_crud = crud.Discussion(db)
        super().__init__(crud.Comment(db))

    def create_comment(self, comment: schemas.CommentCreate,
                       discussion: schemas.DiscussionCreate | None,
                       user: schemas.User) -> models.Comment | None:
        log.info(f"Attempting to create a comment for user {user.username}")

        if discussion is not None:
            discussion_in_db = self.discussion_crud.create(obj_in=discussion)
            comment.discussion_uuid = discussion_in_db.uuid
        elif comment.discussion_uuid is None:
            log.warning(f"Discussion UUID not found, can't create comment without discussion.")
            return None
        else:
            discussion_in_db = self.discussion_crud.get(comment.discussion_uuid)

        if discussion_in_db.state == models.DiscussionState.RESOLVED:
            log.info(f"Discussion {discussion_in_db.uuid} is resolved. Cannot add comment.")
            return None

        document = self.document_crud.get(discussion_in_db.document_uuid)
        if document.doc_state == models.DocumentState.CLOSED:
            log.warning(f"Cannot add comment to a closed document!")
            return None

        if comment.replied_comment_uuid is not None:
            # check if the parent comment isn't from a different discussion
            parent_comment = self.crud.get(comment.replied_comment_uuid)
            if parent_comment.discussion_uuid != comment.discussion_uuid:
                log.warning(
                    f"Parent comment {parent_comment.uuid} belongs to a different discussion. Can't create comment.")
                return None

        # control permissions
        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            discussion_in_db.document_uuid, user.uuid)

        if permission is None:
            log.warning(f"User {user.username} does not have permission to create a comment for discussion {discussion_in_db.uuid}")
            return None

        db_obj_comment_data = schemas.utils.as_dict(comment)
        db_obj_comment_data["user_uuid"] = user.uuid

        created_comment = self.crud.create(obj_in=db_obj_comment_data)
        log.info(f"Comment created with UUID: {created_comment.uuid}")
        return created_comment

    def update_comment(self, uuid: UUID, obj_in: schemas.CommentUpdate, user: schemas.User) -> models.Comment | None:
        log.info(f"Updating comment with UUID: {uuid}")
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            log.warning(f"Comment update failed: No comment found with provided UUID")
            return None

        if obj_to_update.user_uuid != user.uuid:
            log.warning(f"Comment update failed: User {user.username} does not have permission to update this comment")
            return None

        discussion = self.discussion_crud.get(obj_to_update.discussion_uuid)
        document = self.document_crud.get(discussion.document_uuid)
        if document.doc_state == models.DocumentState.CLOSED:
            log.warning(f"Cannot edit comment in a closed document!")
            return None

        comment_update = schemas.utils.as_dict(obj_in)
        comment_update["last_edited_at"] = datetime.utcnow()

        updated_comment = self.crud.update(db_obj=obj_to_update, obj_in=comment_update)
        log.info(f"Comment updated with UUID: {updated_comment.uuid}")
        return updated_comment

    def get_by_discussion_uuid_all(self, discussion_uuid: UUID) -> list[Type[models.Comment]]:
        log.info(f"Fetching all comments for discussion UUID: {discussion_uuid}")
        return self.crud.get_by_discussion_uuid_all(discussion_uuid)

    def get_by_discussion_uuid_multi(self, discussion_uuid: UUID, skip: int = 0, limit: int = 100) -> list[
        Type[models.Comment]]:
        log.info(f"Fetching comments for discussion UUID: {discussion_uuid} with skip: {skip} and limit: {limit}")
        return self.crud.get_by_discussion_uuid_multi(discussion_uuid, skip, limit)
