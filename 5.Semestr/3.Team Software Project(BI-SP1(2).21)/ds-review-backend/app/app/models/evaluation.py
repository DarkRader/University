"""Evaluation ORM model."""
from uuid import uuid4
from enum import Enum
from datetime import datetime
from sqlalchemy import Column, DateTime, ForeignKey, Integer
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship
from sqlalchemy import Enum as SQLEnum

from db.base_class import Base


class EvaluationState(Enum):
    """State of the evaluation.

    - **approved** - Reviewer approved the document.
    - **disapproved** - Reviewer disapproved the document.
    """
    APPROVED = "approved"
    DISAPPROVED = "disapproved"


# pylint: disable=too-few-public-methods
# reason: ORM model does not require to have any public methods
class Evaluation(Base):
    """Comment model to create and manipulate comment entity in the database."""
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    created_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    state = Column(SQLEnum(EvaluationState, name="evaluation_state"),
                   nullable=False)  # type: ignore
    rating = Column(Integer, nullable=True, default=0)
    document_uuid = Column(UUID(as_uuid=True), ForeignKey("document.uuid"), nullable=False)
    user_uuid = Column(UUID(as_uuid=True), ForeignKey("user.uuid"), nullable=False)

    user = relationship("User", back_populates="evaluations")
    document = relationship("Document", back_populates="evaluation")
    discussion = relationship("Discussion", back_populates="evaluation")

# pylint: enable=too-few-public-methods
