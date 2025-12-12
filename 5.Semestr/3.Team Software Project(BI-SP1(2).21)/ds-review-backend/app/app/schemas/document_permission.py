"""DTO schemas for DocumentPermission entity."""
from datetime import datetime
from uuid import UUID

from pydantic import BaseModel

from models.document_permission import DocumentPermissionType


class DocumentPermissionBase(BaseModel):
    """Shared properties of DocumentPermission."""
    permission_type: DocumentPermissionType | None = None


class DocumentPermissionCreate(DocumentPermissionBase):
    """Properties to receive via API on creation."""
    permission_type: DocumentPermissionType
    document_uuid: UUID
    user_uuid: UUID


class DocumentPermissionUpdate(DocumentPermissionBase):
    """Properties to receive via API on update."""
    permission_type: DocumentPermissionType
    granted_at: datetime | None = None


class DocumentPermissionInDBBase(DocumentPermissionBase):
    """Base model for document permission in database."""
    uuid: UUID
    permission_type: DocumentPermissionType
    granted_at: datetime
    document_uuid: UUID
    user_uuid: UUID

    class Config:
        """Config class for database document permission model."""
        orm_mode = True


class DocumentPermission(DocumentPermissionInDBBase):
    """Additional properties of document permission to return via API."""


class DocumentPermissionInDB(DocumentPermissionInDBBase):
    """Additional properties stored in DB"""
