"""
This module defines the CRUD operations for the User model, including an
abstract base class (AbstractCRUDUser) and a concrete implementation (CRUDUser)
using SQLAlchemy.
"""
from datetime import datetime
from abc import ABC, abstractmethod
from typing import List, Type

from sqlalchemy.orm import Session

import models
import schemas

from crud import CRUDBase


class AbstractCRUDUser(CRUDBase[
                           models.User,
                           schemas.UserCreate,
                           schemas.UserUpdate
                       ], ABC):
    """
    Abstract class for CRUD operations specific to the User model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating User instances.
    """

    @abstractmethod
    def get_by_dsr_token(self, dsr_token: str) -> models.User | None:
        """
        Retrieves a User instance by its dsr_token.

        :param dsr_token: The dsr_token of the User.
        :return: The User instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_username(self, username: str) -> models.User | None:
        """
        Retrieves a User instance by its username.

        :param username: The username of the User.
        :return: The User instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_email(self, email: str) -> models.User | None:
        """
        Retrieves a User instance by its email.

        :param email: The email of the User.
        :return: The User instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_registration_in_range_all(self, start_date: datetime, end_date: datetime
                                         ) -> List[models.User]:
        """
        Retrieves all User instances registered within a specified date range.

        :param start_date: The start date of the range.
        :param end_date: The end date of the range.
        :return: A list of User instances.
        """

    @abstractmethod
    def get_by_last_login_in_range_all(self, start_date: datetime, end_date: datetime
                                       ) -> List[models.User]:
        """
        Retrieves all User instances that last logged in within a specified date range.

        :param start_date: The start date of the range.
        :param end_date: The end date of the range.
        :return: A list of User instances.
        """


class CRUDUser(AbstractCRUDUser):
    """
    Concrete class for CRUD operations specific to the User model.
    It extends the abstract AbstractCRUDDocument class and implements the required methods
    for querying and manipulating User instances.
    """

    def __init__(self, db: Session):
        super().__init__(models.User, db)

    def get_by_dsr_token(self, dsr_token: str) -> models.User | None:
        return self.db.query(self.model) \
            .filter(self.model.dsr_token == dsr_token) \
            .first()

    def get_by_username(self, username: str) -> models.User | None:
        return self.db.query(self.model) \
            .filter(self.model.username == username) \
            .first()

    def get_by_email(self, email: str) -> models.User | None:
        return self.db.query(self.model) \
            .filter(self.model.email == email) \
            .first()

    def get_by_registration_in_range_all(self, start_date: datetime, end_date: datetime
                                         ) -> List[Type[models.User]]:
        return self.db.query(self.model) \
            .filter(self.model.registered_at >= start_date,
                    self.model.registered_at <= end_date) \
            .all()

    def get_by_last_login_in_range_all(self, start_date: datetime, end_date: datetime
                                       ) -> List[Type[models.User]]:
        return self.db.query(self.model) \
            .filter(self.model.last_login_at >= start_date,
                    self.model.last_login_at <= end_date) \
            .all()
