"""Discussion ORM model and its dependencies."""
from uuid import uuid4
from datetime import datetime
from enum import Enum
from sqlalchemy import Column, JSON, DateTime, ForeignKey
from sqlalchemy import Enum as SQLEnum
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship

from db.base_class import Base


class DiscussionState(Enum):
    """State of the discussion.

    - **open** - Users can add comments to discussion.
    - **resolved** - Users can no longer add comments to discussion.
    """
    OPEN = "open"
    RESOLVED = "resolved"


# pylint: disable=too-few-public-methods
# reason: ORM model does not require to have any public methods
class Discussion(Base):
    """Discussion model to create and manipulate discussion entity in the database."""
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    crosslink = Column(JSON, nullable=True)
    created_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    resolved_at = Column(DateTime, nullable=True)
    state = Column(SQLEnum(DiscussionState, name="discussion_state"), nullable=False,
                   default=DiscussionState.OPEN)  # type: ignore
    document_uuid = Column(UUID(as_uuid=True), ForeignKey("document.uuid"), nullable=False)
    evaluation_uuid = Column(UUID(as_uuid=True), ForeignKey("evaluation.uuid"), nullable=True)

    document = relationship("Document", back_populates="discussions")
    comments = relationship("Comment", back_populates="discussion")
    evaluation = relationship("Evaluation", back_populates="discussion")

# pylint: enable=too-few-public-methods
