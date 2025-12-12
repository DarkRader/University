"""
API controllers for evaluations.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Body, Path, Query, responses

from api import utils
from api.user_authenticator import get_current_user
import schemas
from services import EvaluationService

router = APIRouter(
    prefix="/evaluations",
    tags=[utils.fastapi_docs.EVALUATION_TAG["name"]]
)


@router.get("/",
            response_model=List[schemas.Evaluation],
            status_code=status.HTTP_200_OK)
async def get_document_evaluations(
        service: Annotated[EvaluationService, Depends(EvaluationService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_uuid: Annotated[UUID, Query()],
) -> Any:
    """
    Get all evaluations for document with uuid equal to document_uuid.

    :param service: Evaluation service.
    :param user: Current user.
    :param document_uuid: uuid of the document.
    """
    evaluations = service.get_by_document_uuid_all(document_uuid, user)
    if evaluations is None:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return evaluations


@router.get("/{evaluation_uuid}",
            response_model=schemas.Evaluation,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_evaluation(
        service: Annotated[EvaluationService, Depends(EvaluationService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        evaluation_uuid: Annotated[UUID, Path()]
) -> Any:
    """
    Get evaluation with uuid equal to evaluation_uuid.

    :param service: Evaluation service.
    :param user: Current user.
    :param evaluation_uuid: uuid of the evaluation.
    """
    evaluation = service.get_evaluation(evaluation_uuid, user)
    if not evaluation:
        raise utils.EntityNotFoundException(utils.Entity.EVALUATION, evaluation_uuid)
    return evaluation


@router.post("/",
             response_model=schemas.Evaluation,
             responses={
                 400: {"model": utils.Message, "description": "Couldn't create evaluation."},
             },
             status_code=status.HTTP_201_CREATED,
             )
async def post_evaluation(service: Annotated[EvaluationService, Depends(EvaluationService)],
                          user: Annotated[schemas.User, Depends(get_current_user)],
                          evaluation: schemas.EvaluationCreate) -> Any:
    """
    Create evaluation.

    :param service: Evaluation service.
    :param user: Current user.
    :param evaluation: EvaluationCreate schema.
    """
    evaluation = service.create_evaluation(evaluation, user)
    if not evaluation:
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                "message": "Could not create evaluation."
            }
        )
    return evaluation


@router.put("/{evaluation_uuid}",
            response_model=schemas.Evaluation,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_evaluation(service: Annotated[EvaluationService, Depends(EvaluationService)],
                            user: Annotated[schemas.User, Depends(get_current_user)],
                            evaluation_uuid: Annotated[UUID, Path()],
                            evaluation: Annotated[schemas.EvaluationUpdate, Body()]) -> Any:
    """
    Update evaluation with uuid equal to evaluation_uuid.

    :param service: Evaluation service.
    :param user: Current user.
    :param evaluation_uuid: uuid of the evaluation.
    :param evaluation: EvaluationUpdate schema.
    """
    updated_evaluation = service.update_evaluation(evaluation_uuid, evaluation, user)
    if not updated_evaluation:
        raise utils.EntityNotFoundException(utils.Entity.EVALUATION, evaluation_uuid)
    return updated_evaluation


@router.delete("/{evaluation_uuid}",
               response_model=schemas.Evaluation,
               responses={
                   **utils.EntityNotFoundException.RESPONSE,
               },
               status_code=status.HTTP_200_OK)
async def delete_evaluation(service: Annotated[EvaluationService, Depends(EvaluationService)],
                            user: Annotated[schemas.User, Depends(get_current_user)],
                            evaluation_uuid: Annotated[UUID, Path()]) -> Any:
    """Delete evaluation with uuid equal to evaluation_uuid.

    :param service: Evaluation service.
    :param user: Current user.
    :param evaluation_uuid: uuid of the evaluation.
    """
    deleted_evaluation = service.remove_evaluation(evaluation_uuid, user)
    if not deleted_evaluation:
        raise utils.EntityNotFoundException(utils.Entity.EVALUATION, evaluation_uuid)
    return deleted_evaluation
