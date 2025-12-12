"""
This module defines the CRUD operations for the Evaluation model, including an
abstract base class (AbstractCRUDEvaluation) and a concrete implementation (CRUDEvaluation)
using SQLAlchemy.
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from sqlalchemy.orm import Session

from crud import CRUDBase
from models import Evaluation, EvaluationState
from schemas import EvaluationCreate, EvaluationUpdate
import models


class AbstractCRUDEvaluation(CRUDBase[
                                 models.Evaluation,
                                 EvaluationCreate,
                                 EvaluationUpdate], ABC):
    """
    Abstract class for CRUD operations specific to the Evaluation model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating Evaluation instances.
    """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[Evaluation]]:
        """
        Retrieve all Evaluation instances for a given document_uuid.

        :param document_uuid: The UUID of the Document.
        :return: A list of Evaluation instances for the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_multi(self, document_uuid: UUID,
                                   skip: int = 0, limit: int = 100) -> list[Type[Evaluation]]:
        """
        Retrieve a paginated list of evaluations for a specific document based on its UUID.

        :param document_uuid: The UUID of the document.
        :param skip: The number of evaluations to skip.
        :param limit: The maximum number of evaluations to return.
        :return: A paginated list of Evaluation instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_state_all(self, document_uuid: UUID, state: EvaluationState) \
            -> list[Type[Evaluation]]:
        """
        Retrieve all evaluations for a specific document based on its UUID and evaluation state.

        :param document_uuid: The UUID of the document.
        :param state: The state of the evaluations.
        :return: A list of Evaluation instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_rating_in_range_all(self, document_uuid: UUID,
                                                     rating_from: int = 0, rating_to: int = 10,
                                                     ) -> list[Type[Evaluation]]:
        """
        Retrieve a list of Evaluation instances associated with a specific document UUID
        within a given rating range.

        :param document_uuid: The UUID of the document for which evaluations are to be retrieved.
        :param rating_from: The lower bound of the rating range (inclusive). Default is 0.
        :param rating_to: The upper bound of the rating range (inclusive). Default is 10.
        :return: A list of Evaluation instances.
        """


class CRUDEvaluation(AbstractCRUDEvaluation):
    """
    Concrete class for CRUD operations specific to the Evaluation model.
    It extends the abstract AbstractCRUDEvaluation class and implements the required methods
    for querying and manipulating Evaluation instances.
    """

    def __init__(self, db: Session):
        super().__init__(models.Evaluation, db)

    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[Evaluation]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .all()

    def get_by_document_uuid_multi(self, document_uuid: UUID,
                                   skip: int = 0, limit: int = 100) -> list[Type[Evaluation]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .order_by(self.model.created_at.desc()) \
            .offset(skip).limit(limit) \
            .all()

    def get_by_document_uuid_and_state_all(self, document_uuid: UUID, state: EvaluationState) \
            -> list[Type[Evaluation]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .filter(self.model.state == state) \
            .all()

    def get_by_document_uuid_and_rating_in_range_all(self, document_uuid: UUID,
                                                     rating_from: int = 0, rating_to: int = 10,
                                                     ) -> list[Type[Evaluation]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .filter(self.model.rating >= rating_from) \
            .filter(self.model.rating <= rating_to) \
            .all()
