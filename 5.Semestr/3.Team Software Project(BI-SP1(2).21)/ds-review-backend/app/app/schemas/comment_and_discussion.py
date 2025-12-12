"""DTO scheme for Comment and Discussion joined operations."""
from pydantic import BaseModel, Field

import schemas


class CommentAndDiscussionCreate(BaseModel):
    """Properties to receive via API on creation of Discussion, and it's first Comment."""
    comment: schemas.CommentCreate = Field(
        default=...,
        description="Don't provide discussion_uuid if you provide a DiscussionCreate schema."
    )
    discussion: schemas.DiscussionCreate | None = Field(
        default=None,
        description="Provide only if you want to create a new discussion."
    )
