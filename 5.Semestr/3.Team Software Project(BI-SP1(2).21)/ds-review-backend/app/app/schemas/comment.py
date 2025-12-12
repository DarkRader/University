"""DTO schemes for Comment entity."""
from datetime import datetime
from uuid import UUID

from pydantic import BaseModel


class CommentBase(BaseModel):
    """Shared properties of Comment."""
    content: str


class CommentCreate(CommentBase):
    """Properties to receive via API on creation."""
    discussion_uuid: UUID | None = None
    replied_comment_uuid: UUID | None = None


class CommentUpdate(CommentBase):
    """Properties to receive via API on update."""


class CommentInDBBase(CommentBase):
    """Base model for comment in database."""
    uuid: UUID
    content: str
    created_at: datetime
    discussion_uuid: UUID
    replied_comment_uuid: UUID | None = None

    # pylint: disable=too-few-public-methods
    # reason: Config class only needs to set orm_mode to True.
    class Config:
        """Config class for database comment model."""
        orm_mode = True


class Comment(CommentInDBBase):
    """Additional properties of comment to return via API."""


class CommentInDB(CommentInDBBase):
    """Additional properties stored in DB"""
