"""DTO schemes for User entity."""
from datetime import datetime
from uuid import UUID

from pydantic import BaseModel


class Token(BaseModel):
    access_token: str
    token_type: str


class TokenData(BaseModel):
    username: str | None = None


class UserBase(BaseModel):
    """Shared properties of User."""
    username: str | None = None
    first_name: str | None = None
    last_name: str | None = None
    email: str | None = None


class UserCreate(UserBase):
    """Properties to receive via API on creation."""
    username: str
    password: str
    first_name: str
    last_name: str
    email: str


class UserUpdate(UserBase):
    """Properties to receive via API on update."""
    first_name: str | None = None
    last_name: str | None = None
    email: str | None = None


class UserUpdatePassword(UserBase):
    """Properties to receive via API on password update."""
    password: str


class UserInDBBase(UserBase):
    """Base model for user in database."""
    uuid: UUID
    dsr_token: str
    username: str
    first_name: str
    last_name: str
    email: str
    disabled: bool
    registered_at: datetime
    last_login_at: datetime | None = None

    # pylint: disable=too-few-public-methods
    # reason: Config class only needs to set orm_mode to True.
    class Config:
        """Config class for database user model."""
        orm_mode = True


class User(UserInDBBase):
    """Additional properties of user to return via API."""


class UserInDB(UserInDBBase):
    """Additional properties stored in DB"""
    password: str
