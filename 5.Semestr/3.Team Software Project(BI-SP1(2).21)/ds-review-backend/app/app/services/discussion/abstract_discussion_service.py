"""
This module defines an abstract base class AbstractDiscussionService that work with Discussion
"""

from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID
from services import CrudServiceBase

import models
import schemas
import crud


class AbstractDiscussionService(CrudServiceBase[
                                    models.Discussion,
                                    crud.Discussion,
                                    schemas.DiscussionCreate,
                                    schemas.DiscussionUpdate,
                                ], ABC):
    """
    This abstract class defines the interface for a discussion service
    that provides CRUD operations for a specific DiscussionModel.
    """

    @abstractmethod
    def get_discussion(self, uuid: UUID, user: models.User) -> models.Discussion | None:
        """
        Retrieve discussion from the database.
        :param uuid: the ID of the discussion to retrieve.
        :param user: the UserSchema for control permissions of the discussion.
        :returns: DiscussionModel.
        """

    @abstractmethod
    def create_discussion(self, discussion: schemas.DiscussionCreate | None,
                          user: schemas.User) \
            -> models.Discussion | None:
        """
        Post discussion to document.
        :param discussion: DiscussionCreate schema.
        :param user: the UserSchema for control permissions of the discussion.
        :returns DiscussionModel: the created object.
        """

    @abstractmethod
    def update_discussion(self, uuid: UUID, obj_in: schemas.DiscussionUpdate, user: models.User) \
            -> models.Discussion | None:
        """
        Update discussion in the database.
        :param uuid: the ID of the discussion to update.
        :param obj_in: the updated discussion.
        :param user: the UserSchema for control permissions of the discussion.
        :returns CommentModel: the updated discussion.
        """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID,
                                 user: schemas.User) -> list[Type[models.Discussion]]:
        """
        Retrieves all Discussion instances with the given document_uuid.
        :param document_uuid: The UUID of the Document.
        :param user: the UserSchema for control permissions of the discussion.
        :return: A list of Discussion instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[models.Discussion]]:
        """
        Retrieves a limited number of Discussion instances with the given document_uuid,
        skipping a specified number of entries.
        :param document_uuid: The UUID of the Document.
        :param skip: The number of Discussion instances to skip.
        :param limit: The maximum number of Discussion instances to return.
        :return: A list of Discussion instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.DiscussionState) \
            -> list[Type[models.Discussion]]:
        """
        Retrieves all Discussion instances with the given document_uuid and given state.
        :param document_uuid: The UUID of the Document.
        :param state: The state of the Discussion
        :return: A list of Discussion instances with the given document_uuid.
        """
