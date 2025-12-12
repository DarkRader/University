"""Document Permission ORM model."""
from enum import Enum
from uuid import uuid4
from datetime import datetime
from sqlalchemy import Column, DateTime, ForeignKey
from sqlalchemy import Enum as SQLEnum
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship

from db.base_class import Base


class DocumentPermissionType(Enum):
    """
    Type of the permission.

    - **submitter** - Own the document.
    - **reviewer** - Can review the document.
    """
    SUBMITTER = "submitter"
    REVIEWER = "reviewer"


# pylint: disable=too-few-public-methods
# reason: ORM model does not require to have any public methods
class DocumentPermission(Base):
    """Comment model to create and manipulate comment entity in the database."""
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    permission_type = Column(SQLEnum(DocumentPermissionType, name="document_permission_type"), nullable=False)  # type: ignore
    granted_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    document_uuid = Column(UUID(as_uuid=True), ForeignKey("document.uuid"), nullable=False)
    user_uuid = Column(UUID(as_uuid=True), ForeignKey("user.uuid"), nullable=False)

    user = relationship("User", back_populates="document_permissions")
    document = relationship("Document", back_populates="document_permissions")

# pylint: enable=too-few-public-methods
