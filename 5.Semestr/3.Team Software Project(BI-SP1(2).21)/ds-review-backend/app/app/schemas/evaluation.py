"""DTO schemes for Evaluation entity."""
from datetime import datetime
from uuid import UUID
from pydantic import BaseModel

from models.evaluation import EvaluationState


class EvaluationBase(BaseModel):
    """Shared properties of Evaluation."""
    state: EvaluationState | None = None
    rating: int | None = None


class EvaluationCreate(EvaluationBase):
    """Properties to receive via API on creation."""
    state: EvaluationState
    rating: int
    document_uuid: UUID


class EvaluationUpdate(EvaluationBase):
    """Properties to receive via API on update."""


class EvaluationInDBBase(EvaluationBase):
    """Base model for evaluation in the database."""
    uuid: UUID
    created_at: datetime
    state: EvaluationState
    rating: int
    document_uuid: UUID

    class Config:  # pylint: disable=too-few-public-methods
        """Config class for database evaluation model."""
        orm_mode = True


class Evaluation(EvaluationInDBBase):
    """Additional properties of evaluation to return via API."""


class EvaluationInDB(EvaluationInDBBase):
    """Additional properties stored in DB"""
