"""DTO schemes for Discussion entity."""
from datetime import datetime
from uuid import UUID

from pydantic import BaseModel

from models.discussion import DiscussionState
from schemas import Comment


class Crosslink(BaseModel):
    """Crosslink of Discussion to determine Discussion's position in document."""
    start_index: int
    end_index: int
    element_ids: list[str]


class DiscussionBase(BaseModel):
    """Shared properties of Discussion."""
    crosslink: Crosslink | None = None


class DiscussionCreate(DiscussionBase):
    """Properties to receive via API on creation."""
    document_uuid: UUID
    evaluation_uuid: UUID | None = None


class DiscussionUpdate(DiscussionBase):
    """Properties to receive via API on update."""
    state: DiscussionState | None = None


class DiscussionInDBBase(DiscussionBase):
    """Base model for discussion in database."""
    uuid: UUID
    state: DiscussionState
    created_at: datetime
    resolved_at: datetime | None = None
    document_uuid: UUID
    evaluation_uuid: UUID | None = None
    comments: list[Comment]

    # pylint: disable=too-few-public-methods
    # reason: Config class only needs to set orm_mode to True.
    class Config:
        """Config class for database discussion model."""
        orm_mode = True


class Discussion(DiscussionInDBBase):
    """Additional properties of discussion to return via API."""


class DiscussionInDB(DiscussionInDBBase):
    """Additional properties stored in DB"""
