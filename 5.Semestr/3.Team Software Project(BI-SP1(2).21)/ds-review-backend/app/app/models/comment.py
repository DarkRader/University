"""Comment ORM model."""
from uuid import uuid4
from datetime import datetime
from sqlalchemy import Column, String, DateTime, ForeignKey
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship

from db.base_class import Base


# pylint: disable=too-few-public-methods
# reason: ORM model does not require to have any public methods
class Comment(Base):
    """Comment model to create and manipulate comment entity in the database."""
    uuid = Column(UUID(as_uuid=True), primary_key=True, default=uuid4)
    content = Column(String, nullable=False)
    created_at = Column(DateTime, nullable=False, default=datetime.utcnow)
    last_edited_at = Column(DateTime, nullable=True)
    discussion_uuid = Column(UUID(as_uuid=True), ForeignKey("discussion.uuid"))
    replied_comment_uuid = Column(UUID(as_uuid=True), ForeignKey("comment.uuid"), nullable=True)
    user_uuid = Column(UUID(as_uuid=True), ForeignKey("user.uuid"), nullable=False)

    user = relationship("User", back_populates="comments")
    discussion = relationship("Discussion", back_populates="comments")
    replied_comment = relationship("Comment")

# pylint: enable=too-few-public-methods
