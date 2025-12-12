"""
This module defines an abstract base class AbstractEvaluationService that work with Evaluation
"""

from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID
from services import CrudServiceBase

import models
import schemas
import crud


class AbstractEvaluationService(CrudServiceBase[
                                    models.Evaluation,
                                    crud.Evaluation,
                                    schemas.EvaluationCreate,
                                    schemas.EvaluationUpdate,
                                ], ABC):
    """
    This abstract class defines the interface for an evaluation service
    that provides CRUD operations for a specific EvaluationModel.
    """

    @abstractmethod
    def get_evaluation(self, uuid: UUID, user: schemas.User) -> models.Evaluation | None:
        """
        Retrieve evaluation from the database.
        :param uuid: the ID of the evaluation to retrieve.
        :param user: the UserSchema for control permissions of the evaluation.
        :returns: EvaluationModel.
        """

    @abstractmethod
    def create_evaluation(self, evaluation: schemas.EvaluationCreate,
                          user: schemas.User) \
            -> models.Evaluation | None:
        """
        Post evaluation to document.
        :param evaluation: EvaluationCreate schema.
        :param user: the UserSchema for control permissions of the evaluation.
        :returns EvaluationModel: the created evaluation.
        """

    @abstractmethod
    def update_evaluation(self, uuid: UUID, obj_in: schemas.EvaluationUpdate, user: models.User) \
            -> models.Evaluation | None:
        """
        Update evaluation in the database.
        :param uuid: the ID of the evaluation to update.
        :param obj_in: the updated evaluation.
        :param user: the UserSchema for control permissions of the evaluation.
        :returns EvaluationModel: the updated evaluation.
        """

    @abstractmethod
    def remove_evaluation(self, uuid: UUID | None, user: schemas.User) -> models.Evaluation | None:
        """
        Delete evaluation from the database.
        :param uuid: the ID of the evaluation to delete.
        :param user: the UserSchema for control permissions of the evaluation.
        :returns EvaluationModel: the removed evaluation.
        """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID,
                                 user: schemas.User) \
            -> list[Type[models.Evaluation]] | None:
        """
        Retrieves all Evaluations instances with the given document_uuid.
        :param document_uuid: The UUID of the Document.
        :param user: the UserSchema for control permissions of the evaluation.
        :return: A list of Evaluation instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_multi(self, document_uuid: UUID,
                                   skip: int = 0, limit: int = 100) \
            -> list[Type[models.Evaluation]]:
        """
        Retrieve a paginated list of evaluations for a specific document based on its UUID.

        :param document_uuid: The UUID of the document.
        :param skip: The number of evaluations to skip.
        :param limit: The maximum number of evaluations to return.
        :return: A paginated list of Evaluation instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.EvaluationState) \
            -> list[Type[models.Evaluation]]:
        """
        Retrieve all evaluations for a specific document based on its UUID and evaluation state.

        :param document_uuid: The UUID of the document.
        :param state: The state of the evaluations.
        :return: A list of Evaluation instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_rating__all(self, document_uuid: UUID,
                                             rating: int,
                                             ) -> list[Type[models.Evaluation]]:
        """
        Retrieve a list of Evaluation instances associated with a specific document UUID
        within a given rating range.

        :param document_uuid: The UUID of the document for which evaluations are to be retrieved.
        :param rating: The rating of the evaluations.
        :return: A list of Evaluation instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_rating_in_range_all(self, document_uuid: UUID,
                                                     rating_from: int = 0, rating_to: int = 10,
                                                     ) -> list[Type[models.Evaluation]]:
        """
        Retrieve a list of Evaluation instances associated with a specific document UUID
        within a given rating range.

        :param document_uuid: The UUID of the document for which evaluations are to be retrieved.
        :param rating_from: The lower bound of the rating range (inclusive). Default is 0.
        :param rating_to: The upper bound of the rating range (inclusive). Default is 10.
        :return: A list of Evaluation instances.
        """
