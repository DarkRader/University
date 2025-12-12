"""
This module defines an abstract base class AbstractCommentService that work with Comment
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from services import CrudServiceBase

import models
import schemas
import crud


class AbstractCommentService(CrudServiceBase[
                                 models.Comment,
                                 crud.Comment,
                                 schemas.CommentCreate,
                                 schemas.CommentUpdate,
                             ], ABC):
    """
    This abstract class defines the interface for a comment service
    that provides CRUD operations for a specific CommentModel.
    """

    @abstractmethod
    def create_comment(self, comment: schemas.CommentCreate,
                       discussion: schemas.DiscussionCreate | None,
                       user: schemas.User)\
            -> models.Comment | None:
        """
        Post comment to document with uuid equal to document_uuid.
        If a comment is attached to a non-existent discussion,
        a new discussion is created.
        :param comment: CommentCreate schema.
        :param discussion: DiscussionCreate schema.
        :param user: the UserSchema for control permissions of the comment.
        :returns CommentModel: the created object.
        """

    @abstractmethod
    def update_comment(self, uuid: UUID, obj_in: schemas.CommentUpdate, user: models.User) \
            -> models.Comment | None:
        """
        Update comment in the database.
        :param uuid: the ID of the comment to update.
        :param obj_in: the updated comment.
        :param user: the UserSchema for control permissions of the comment.
        :returns CommentModel: the updated comment.
        """

    @abstractmethod
    def get_by_discussion_uuid_all(self, discussion_uuid: UUID) -> list[Type[models.Comment]]:
        """
        Retrieves all Comment instances with the given discussion_uuid.
        :param discussion_uuid: The UUID of the Discussion.
        :return: A list of Comments instances with the given discussion_uuid.
        """

    @abstractmethod
    def get_by_discussion_uuid_multi(self, discussion_uuid: UUID,
                                     skip: int = 0, limit: int = 100) -> list[Type[models.Comment]]:
        """
        Retrieves a limited number of Comment instances with the given discussion_uuid,
        skipping a specified number of entries.
        :param discussion_uuid: The UUID of the Discussion.
        :param skip: The number of Comment instances to skip.
        :param limit: The maximum number of Comment instances to return.
        :return: A list of Comment instances.
        """
