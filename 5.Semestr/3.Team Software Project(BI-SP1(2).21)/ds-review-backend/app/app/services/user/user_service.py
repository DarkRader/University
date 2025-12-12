"""
This module defines class UserService that work with User
"""
import logging
from datetime import datetime
from typing import Annotated, List, Type
from fastapi import Depends

import crud
import models
from db import get_db

from services import AbstractUserService
from sqlalchemy.orm import Session

log = logging.getLogger(__name__)


class UserService(AbstractUserService):
    """
    Class UserService represent service that work with User
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        super().__init__(crud.User(db))

    def get_by_dsr_token(self, dsr_token: str) -> models.User:
        log.info(f"Getting user by {dsr_token = }")
        return self.crud.get_by_dsr_token(dsr_token)

    def get_by_username(self, username: str) -> models.User:
        log.info(f"Getting user by {username = }")
        return self.crud.get_by_username(username)

    def get_by_email(self, email: str) -> models.User:
        log.info(f"Getting user by {email = }")
        return self.crud.get_by_email(email)

    def get_by_registration_in_range_all(self, start_date: datetime, end_date: datetime
                                         ) -> List[Type[models.User]]:
        log.info(f"Getting user by registration in range from {start_date} to {end_date}")
        return self.crud.get_by_registration_in_range_all(start_date, end_date)

    def get_by_last_login_in_range_all(self, start_date: datetime, end_date: datetime
                                       ) -> List[Type[models.User]]:
        log.info(f"Getting user by last login in range from {start_date} to {end_date}")
        return self.crud.get_by_last_login_in_range_all(start_date, end_date)
