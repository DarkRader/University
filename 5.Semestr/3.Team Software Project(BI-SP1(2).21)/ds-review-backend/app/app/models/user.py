"""User ORM model and its dependencies."""
from uuid import uuid4
from datetime import datetime
from sqlalchemy import Boolean, Column, String, DateTime
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship

from db.base_class import Base


class User(Base):
    """
    User model to create and manipulate user entity in the database.
    """
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    dsr_token = Column(String, unique=True, nullable=False, default=lambda: f"dsr-{uuid4()}")
    username = Column(String, unique=True, nullable=False)
    password = Column(String, nullable=False)
    first_name = Column(String, nullable=False)
    last_name = Column(String, nullable=False)
    email = Column(String, unique=True, nullable=False)
    disabled = Column(Boolean, nullable=False, default=False)
    registered_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    last_login_at = Column(DateTime, nullable=True)

    evaluations = relationship("Evaluation", back_populates="user")
    comments = relationship("Comment", back_populates="user")
    document_permissions = relationship("DocumentPermission", back_populates="user")
