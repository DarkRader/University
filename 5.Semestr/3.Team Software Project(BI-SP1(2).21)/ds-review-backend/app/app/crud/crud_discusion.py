"""
This module defines the CRUD operations for the Comment model, including an
abstract base class (AbstractCRUDComment) and a concrete implementation (CRUDComment)
using SQLAlchemy.
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from sqlalchemy.orm import Session

import models
import schemas
import crud

from crud import CRUDBase
from models import Discussion


class AbstractCRUDDiscussion(CRUDBase[
                                 models.Discussion,
                                 schemas.DiscussionCreate,
                                 schemas.DocumentUpdate
                             ], ABC):
    """
    Abstract class for CRUD operations specific to the Discussion model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating Discussion instances.
    """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[Discussion]] | None:
        """
        Retrieves all Discussion instances with the given document_uuid.

        :param document_uuid: The UUID of the Document.
        :return: A list of Discussion instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[Discussion]]:
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
                                           state: models.DiscussionState) -> list[Type[Discussion]]:
        """
        Retrieves all Discussion instances with the given document_uuid and given state.

        :param document_uuid: The UUID of the Document.
        :param state: The state of the Discussion
        :return: A list of Discussion instances with the given document_uuid.
        """


class CRUDDiscussion(AbstractCRUDDiscussion, ABC):
    """
    Concrete class for CRUD operations specific to the Discussion model.
    It extends the abstract AbstractCRUDDocument class and implements the required methods
    for querying and manipulating Discussion instances.
    """

    def __init__(self, db: Session):
        self.document_crud = crud.Document(db)
        super().__init__(models.Discussion, db)

    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[Discussion]] | None:
        document = self.document_crud.get(document_uuid)
        if not document:
            return None

        return document.discussions

    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[Discussion]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .order_by(self.model.created_at.asc()) \
            .offset(skip).limit(limit) \
            .all()

    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.DiscussionState) -> list[Type[Discussion]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid and self.model.state == state) \
            .all()
