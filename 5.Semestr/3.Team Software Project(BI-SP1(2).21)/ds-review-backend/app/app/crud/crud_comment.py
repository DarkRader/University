"""
This module defines the CRUD operations for the Comment model, including an
abstract base class (AbstractCRUDComment) and a concrete implementation (CRUDComment)
using SQLAlchemy.
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from sqlalchemy.orm import Session

import models
import schemas
import crud

from crud import CRUDBase
from models import Comment


class AbstractCRUDComment(CRUDBase[
                              models.Comment,
                              schemas.CommentCreate,
                              schemas.CommentUpdate
                          ], ABC):
    """
    Abstract class for CRUD operations specific to the Comment model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating Comment instances.
    """

    @abstractmethod
    def get_by_discussion_uuid_all(self, discussion_uuid: UUID) -> list[Type[Comment]]  | None:
        """
        Retrieves all Comment instances with the given discussion_uuid.

        :param discussion_uuid: The UUID of the Discussion.
        :return: A list of Comments instances with the given discussion_uuid.
        """

    @abstractmethod
    def get_by_discussion_uuid_multi(self, discussion_uuid: UUID,
                                     skip: int = 0, limit: int = 100) -> list[Type[Comment]]:
        """
        Retrieves a limited number of Comment instances with the given discussion_uuid,
        skipping a specified number of entries.

        :param discussion_uuid: The UUID of the Discussion.
        :param skip: The number of Comment instances to skip.
        :param limit: The maximum number of Comment instances to return.
        :return: A list of Comment instances.
        """


class CRUDComment(AbstractCRUDComment, ABC):
    """
    Concrete class for CRUD operations specific to the Comment model.
    It extends the abstract AbstractCRUDDocument class and implements the required methods
    for querying and manipulating Comment instances.
    """

    def __init__(self, db: Session):
        self.discussion_crud = crud.Discussion(db)
        super().__init__(models.Comment, db)

    def get_by_discussion_uuid_all(self, discussion_uuid: UUID) -> list[Type[Comment]] | None:
        discussion = self.discussion_crud.get(discussion_uuid)
        if not discussion:
            return None

        return discussion.comments

    def get_by_discussion_uuid_multi(self, discussion_uuid: UUID,
                                     skip: int = 0, limit: int = 100) -> list[Type[Comment]]:
        return self.db.query(self.model) \
            .filter(self.model.discussion_uuid == discussion_uuid) \
            .order_by(self.model.created_at.asc()) \
            .offset(skip).limit(limit) \
            .all()
