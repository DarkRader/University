"""
This module defines an abstract base class AbstractUserService that work with User
"""
from datetime import datetime
from abc import ABC, abstractmethod
from typing import Type, List
from services import CrudServiceBase

import models
import schemas
import crud


class AbstractUserService(CrudServiceBase[
                              models.User,
                              crud.User,
                              schemas.UserCreate,
                              schemas.UserUpdate,
                          ], ABC):
    """
    This abstract class defines the interface for a user service
    that provides CRUD operations for a specific UserModel.
    """

    @abstractmethod
    def get_by_dsr_token(self, dsr_token: str) -> models.User:
        """
        Retrieves a User instance by its dsr_token.

        :param dsr_token: The dsr_token of the User.
        :return: The User instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_username(self, username: str) -> list[Type[models.User]]:
        """
        Retrieves a User instance by its username.

        :param username: The username of the User.
        :return: The User instance if found, None otherwise.
        """

    @abstractmethod
    def get_by_email(self, email: str) -> models.User:
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
