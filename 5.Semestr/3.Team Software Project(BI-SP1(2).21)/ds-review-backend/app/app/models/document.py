"""
Module which includes Document ORM model and its dependencies.
"""
from uuid import uuid4
from datetime import datetime
from enum import Enum
from sqlalchemy import Column, String, DateTime
from sqlalchemy import Enum as SQLEnum
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship

from db.base_class import Base


class DocumentState(Enum):
    """
    State of the document.

    - **open** - Everyone can view and comment the document.
    - **closed** - Only submitter can view the document, no one can comment on it.
    """
    OPEN = "open"
    CLOSED = "closed"


class DocumentType(Enum):
    """
    Type of the document.

    - **html** - HTML document.
    - **json** - JSON document.
    - **plain_text** - Every other document.
    """
    HTML = "html"
    PLAIN_TEXT = "plain_text"
    JSON = "json"


# ORM model does not require to have any public methods
# pylint: disable=too-few-public-methods
class Document(Base):
    """
    Used to create and manipulate document entity in the database.
    """
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    uuid_submission = Column(UUID(as_uuid=True), unique=True, nullable=False, default=uuid4)
    title = Column(String, nullable=False)
    content = Column(String, nullable=False)
    submitted_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    closed_at = Column(DateTime, nullable=True)
    doc_state = Column(SQLEnum(DocumentState, name="document_state"), nullable=False,
                       default=DocumentState.OPEN)  # type: ignore
    doc_type = Column(SQLEnum(DocumentType, name="document_type"), nullable=False)  # type: ignore

    discussions = relationship("Discussion", back_populates="document")
    evaluation = relationship("Evaluation", back_populates="document")
    document_permissions = relationship("DocumentPermission", back_populates="document")

# pylint: enable=too-few-public-methods
