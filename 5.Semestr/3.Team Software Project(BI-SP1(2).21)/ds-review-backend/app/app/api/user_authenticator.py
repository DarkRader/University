from datetime import timedelta, datetime
from typing import Annotated, Optional

from fastapi import Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer
from jose import JWTError, jwt
from passlib.context import CryptContext

from core import settings
from schemas.user import TokenData, User
from services import UserService

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

# tokenUrl must be the same as the login_for_access_token endpoint url
oauth2_scheme = OAuth2PasswordBearer(tokenUrl=f"users/login")


def authenticate_user(user_service: UserService, username: str, password: str):
    """
    Authenticate a user using their username and password.

    :param user_service: User service
    :param username: The username.
    :param password: The password.

    :return: The authenticated user object if successful, otherwise False.
    """
    user = user_service.get_by_username(username)
    if not user:
        return False
    if not verify_password(plain_password=password, hashed_password=user.password):
        return False
    return user


def verify_password(plain_password, hashed_password):
    """
    Verify if a plain text password matches its hashed version.

    :param plain_password: The plain text password.
    :param hashed_password: The hashed password.

    :return: True if the password matches the hash, otherwise False.
    """
    return pwd_context.verify(plain_password, hashed_password)


def get_password_hash(password):
    """
    Hash plain text password.

    :param password: The plain text password.

    :return: The hashed version of the password.
    """
    return pwd_context.hash(password)


async def get_current_user(token: Annotated[str, Depends(oauth2_scheme)],
                           user_service: Annotated[UserService, Depends(UserService)]):
    """
    Retrieve the current user based on a JWT token.

    :param token: JWT token for user identification.
    :param user_service: User service.

    :return: User object.
   """
    credentials_exception = HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Could not validate credentials",
        headers={"WWW-Authenticate": "Bearer"},
    )
    try:
        payload = TokenManager.decode_token(token)
        username: Optional[str] = payload.get("sub")
        if username is None:
            raise credentials_exception
        token_data = TokenData(username=username)
    except JWTError:
        raise credentials_exception
    user = user_service.get_by_username(token_data.username)
    if user is None:
        raise credentials_exception
    return user


async def get_current_active_user(current_user: Annotated[User, Depends(get_current_user)]):
    """
    Check if the current user is active.

    :param current_user: Current user object.

    :return: The current active user.
    """
    if current_user.disabled:
        raise HTTPException(status_code=400, detail="Inactive user")
    return current_user


class TokenManager:
    """
    Class responsible for JWT token creation and decoding.

    Attributes:
        SECRET_KEY: Secret key used for JWT encoding.
        ALGORITHM: Algorithm used for JWT encoding.
        ACCESS_TOKEN_EXPIRE_MINUTES: Expiration time in minutes for the access token.
    """

    # to get a string like this run: openssl rand -hex 32
    SECRET_KEY = settings.JWT_KEY
    ALGORITHM = "HS256"
    ACCESS_TOKEN_EXPIRE_MINUTES = 30

    @staticmethod
    def create_access_token(data: dict, expires_delta: timedelta = timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)):
        """
       Create a JWT access token.

       :param data: Data to encode in the token.
       :param expires_delta: Duration until token expiration.

       :return: JWT access token.
       """
        to_encode = data.copy()
        expire = datetime.utcnow() + expires_delta
        to_encode.update({"exp": expire})
        encoded_jwt = jwt.encode(to_encode, TokenManager.SECRET_KEY, algorithm=TokenManager.ALGORITHM)
        return encoded_jwt

    @staticmethod
    def decode_token(token: str) -> dict:
        """
        Decode a JWT token.

        :param token: JWT token.

        :return: The decoded data.
        """
        return jwt.decode(token, TokenManager.SECRET_KEY, algorithms=[TokenManager.ALGORITHM])
