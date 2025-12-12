"""
This module defines class EvaluationService that work with Evaluation
"""
import logging
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractEvaluationService
from sqlalchemy.orm import Session

log = logging.getLogger(__name__)


class EvaluationService(AbstractEvaluationService):
    """
    Class EvaluationService represent service that work with Evaluation
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_permission_crud = crud.DocumentPermission(db)
        self.document_crud = crud.Document(db)
        super().__init__(crud.Evaluation(db))

    def get_evaluation(self, uuid: UUID, user: models.User) -> models.Evaluation | None:
        log.info(f"Retrieving evaluation with UUID: {uuid}")
        # control permissions
        evaluation = self.crud.get(uuid)
        if evaluation is None:
            log.warning(f"Evaluation not found for UUID: {uuid}")

        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            evaluation.document_uuid, user.uuid)

        if permission is None:
            log.warning(f"Unauthorized access to evaluation with UUID: {uuid}")
            return None

        return evaluation

    def create_evaluation(self, evaluation: schemas.EvaluationCreate,
                          user: schemas.User) \
            -> models.Evaluation | None:
        log.info("Attempting to create a new evaluation")
        # control permissions
        permission = self.document_permission_crud.\
            get_by_document_uuid_user_uuid_and_permission_type(
                evaluation.document_uuid, user.uuid, models.DocumentPermissionType.REVIEWER)

        document = self.document_crud.get(evaluation.document_uuid)
        if document is None:
            log.warning("Cannot create evaluation for non-existing document with "
                        "UUID: {evaluation.document_uuid}")
            return None

        if permission is None:
            log.warning(f"Unauthorized attempt to create evaluation for document with "
                        f"UUID: {evaluation.document_uuid}")
            return None

        if document.doc_state == models.DocumentState.CLOSED:
            log.warning(f"Cannot add evaluation to a closed document!")
            return None

        if evaluation.rating < 0 or evaluation.rating > 10:
            log.warning("Evaluation creation failed: Invalid rating")
            return None

        if not user:
            log.warning("Evaluation creation failed: User is None")
            return None

        db_obj_evaluation_data = schemas.utils.as_dict(evaluation)
        db_obj_evaluation_data["user_uuid"] = user.uuid
        created_evaluation = self.crud.create(obj_in=db_obj_evaluation_data)
        log.info(f"Evaluation created with UUID: {created_evaluation.uuid}")
        return created_evaluation

    def update_evaluation(self, uuid: UUID, obj_in: schemas.EvaluationUpdate, user: schemas.User) \
            -> models.Evaluation | None:
        log.info(f"Updating evaluation with UUID: {uuid}")
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            log.warning(f"Evaluation update failed: No evaluation found with UUID: {uuid}")
            return None

        if obj_to_update.user_uuid != user.uuid:
            log.warning(f"User {user.uuid} cannot update evaluation created by user "
                        f"{obj_to_update.user_uuid}")
            return None

        document = self.document_crud.get(obj_to_update.document_uuid)
        if document.doc_state == models.DocumentState.CLOSED:
            log.warning(f"Cannot edit evaluation in a closed document!")
            return None

        evaluation_update = schemas.utils.as_dict(obj_in)
        updated_evaluation = self.crud.update(db_obj=obj_to_update, obj_in=evaluation_update)
        log.info(f"Evaluation updated with UUID: {updated_evaluation.uuid}")
        return updated_evaluation

    def remove_evaluation(self, uuid: UUID | None, user: schemas.User) -> models.Evaluation | None:
        log.info(f"Removing evaluation with UUID: {uuid}")
        # control permissions
        evaluation = self.get(uuid)

        if evaluation.user_uuid != user.uuid:
            log.warning(f"User with UUID {user.uuid} cannot remove evaluation with UUID: {uuid}")
            return None

        removed_evaluation = self.crud.remove(uuid)
        if removed_evaluation is None:
            log.warning(f"Failed to remove evaluation with UUID: {uuid}")
        return removed_evaluation

    def get_by_document_uuid_all(self, document_uuid: UUID,
                                 user: schemas.User) -> list[Type[models.Evaluation]] | None:
        log.info(f"Fetching all evaluations for document UUID: {document_uuid}")
        # control permissions
        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            document_uuid, user.uuid)

        if permission is None:
            log.warning(f"Unauthorized access to evaluations for document UUID: {document_uuid}")
            return None

        return self.crud.get_by_document_uuid_all(document_uuid)

    def get_by_document_uuid_multi(self, document_uuid: UUID,
                                   skip: int = 0, limit: int = 100) \
            -> list[Type[models.Evaluation]]:
        log.info(f"Fetching evaluations for document UUID: {document_uuid}, skip: {skip}, limit: {limit}")
        return self.crud.get_by_document_uuid_multi(document_uuid, skip, limit)

    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.EvaluationState) \
            -> list[Type[models.Evaluation]]:
        log.info(f"Fetching evaluations for document UUID: {document_uuid} with state: {state}")
        return self.crud.get_by_document_uuid_and_state_all(document_uuid, state)

    def get_by_document_uuid_and_rating__all(self, document_uuid: UUID,
                                             rating: int,
                                             ) -> list[Type[models.Evaluation]]:
        log.info(f"Fetching evaluations for document UUID: {document_uuid} with rating: {rating}")
        return self.crud.get_by_document_uuid_and_rating_in_range_all(document_uuid,
                                                                      rating,
                                                                      rating)

    def get_by_document_uuid_and_rating_in_range_all(self, document_uuid: UUID,
                                                     rating_from: int = 0, rating_to: int = 10,
                                                     ) -> list[Type[models.Evaluation]]:
        log.info(
            f"Fetching evaluations for document UUID: {document_uuid} with rating range: {rating_from} to {rating_to}")
        return self.crud.get_by_document_uuid_and_rating_in_range_all(document_uuid,
                                                                      rating_from,
                                                                      rating_to)
