"""DTO schemes for Document entity."""
from datetime import datetime
from uuid import UUID

from pydantic import BaseModel

from models.document import DocumentState, DocumentType
from schemas import Discussion


class DocumentBase(BaseModel):
    """Shared properties of Document."""
    title: str | None = None
    doc_state: DocumentState | None = None


class DocumentCreate(DocumentBase):
    """Properties to receive via API on creation."""
    title: str
    doc_type: DocumentType
    content: str  # str for now


class DocumentUpdate(DocumentBase):
    """Properties to receive via API on update."""


class DocumentInDBBase(DocumentBase):
    """Base model for document in database."""
    uuid: UUID
    doc_type: DocumentType
    content: str  # str for now
    submitted_at: datetime
    closed_at: datetime | None = None
    discussions: list[Discussion]

    class Config:  # pylint: disable=too-few-public-methods
        """Config class for database document model."""
        orm_mode = True


class Document(DocumentInDBBase):
    """Additional properties of document to return via API."""


class DocumentSubmitter(Document):
    """Additional properties of document to return via API to submitter."""
    uuid_submission: UUID


class DocumentInDB(DocumentInDBBase):
    """Additional properties stored in DB"""
    uuid_submission: UUID
