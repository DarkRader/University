"""
This module defines the CRUD operations for the Document model, including an
abstract base class (AbstractCRUDDocument) and a concrete implementation (CRUDDocument)
using SQLAlchemy.
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from sqlalchemy.orm import Session

import models
import schemas

from crud import CRUDBase
from models import Document


class AbstractCRUDDocument(CRUDBase[
                               models.Document,
                               schemas.DocumentCreate,
                               schemas.DocumentUpdate
                           ], ABC):
    """
    Abstract class for CRUD operations specific to the Document model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating Document instances.
    """

    @abstractmethod
    def get_by_submission_uuid(self, uuid_submission: UUID) -> models.Document | None:
        """
        Retrieves a Document instance by its public UUID.

        :param uuid_submission: The submission UUID of the Document.
        :return: The Document instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_state_all(self, doc_state: models.DocumentState) -> list[Type[Document]]:
        """
        Retrieves all Document instances with the given state.

        :param doc_state: The state of the Documents.
        :return: A list of Document instances with the given state.
        """

    @abstractmethod
    def get_by_state_multi(self, doc_state: models.DocumentState,
                           skip: int = 0, limit: int = 100) -> list[Type[Document]]:
        """
        Retrieves a limited number of Document instances with the given state,
        skipping a specified number of entries.

        :param doc_state: The state of the Documents.
        :param skip: The number of Document instances to skip.
        :param limit: The maximum number of Document instances to return.
        :return: A list of Document instances.
        """

    @abstractmethod
    def get_by_type_multi(self, doc_type: models.DocumentType,
                          skip: int = 0, limit: int = 100) -> list[Type[Document]]:
        """
        Retrieves a limited number of Document instances with the given type,
        skipping a specified number of entries.

        :param doc_type: The type of the Documents.
        :param skip: The number of Document instances to skip.
        :param limit: The maximum number of Document instances to return.
        :return: A list of Document instances.
        """

    @abstractmethod
    def get_by_type_all(self, doc_type: models.DocumentType) -> list[Type[Document]]:
        """
         Retrieves all Document instances with the given type.

         :param doc_type: The type of the Documents.
         :return: A list of Document instances with the given type.
         """


class CRUDDocument(AbstractCRUDDocument):
    """
    Concrete class for CRUD operations specific to the Document model.
    It extends the abstract AbstractCRUDDocument class and implements the required methods
    for querying and manipulating Document instances.
    """

    def __init__(self, db: Session):
        super().__init__(models.Document, db)

    def get_by_submission_uuid(self, uuid_submission: UUID) -> models.Document | None:
        return self.db.query(self.model) \
            .filter(self.model.uuid_submission == uuid_submission) \
            .first()

    def get_by_state_all(self, doc_state: models.DocumentState) -> list[Type[Document]]:
        return self.db.query(self.model) \
            .filter(self.model.doc_state == doc_state) \
            .all()

    def get_by_state_multi(self, doc_state: models.DocumentState,
                           skip: int = 0, limit: int = 100) -> list[Type[Document]]:
        return self.db.query(self.model) \
            .filter(self.model.doc_state == doc_state) \
            .order_by(self.model.submitted_at.desc()) \
            .offset(skip).limit(limit) \
            .all()

    def get_by_type_multi(self, doc_type: models.DocumentType,
                          skip: int = 0, limit: int = 100) -> list[Type[Document]]:
        return self.db.query(self.model) \
            .filter(self.model.doc_type == doc_type) \
            .order_by(self.model.submitted_at.desc()) \
            .offset(skip).limit(limit) \
            .all()

    def get_by_type_all(self, doc_type: models.DocumentType) -> list[Type[Document]]:
        return self.db.query(self.model) \
            .filter(self.model.doc_state == doc_type) \
            .all()
