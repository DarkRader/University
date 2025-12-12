from typing import Annotated, Any

from api import utils
from fastapi import Depends, HTTPException, status, APIRouter, responses
from fastapi.security import OAuth2PasswordRequestForm

from api.user_authenticator import authenticate_user, get_current_user, get_password_hash, TokenManager
import schemas
from services import UserService

router = APIRouter(
    prefix="/users",
    tags=[utils.fastapi_docs.USER_TAG["name"]]
)


@router.post("/login",
             response_model=schemas.Token
             )
async def login(service: Annotated[UserService, Depends(UserService)],
                form_data: Annotated[OAuth2PasswordRequestForm, Depends()],
                ) -> Any:
    """
    Authenticate a user and return an access token, if successful.

    :param service: User service
    :param form_data: Form data containing 'username' and 'password'.

    :return: A JSON object with access token and token type.
    """
    user = authenticate_user(service, form_data.username, form_data.password)
    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Incorrect username or password",
            headers={"WWW-Authenticate": "Bearer"},
        )
    access_token = TokenManager.create_access_token(data={"sub": user.username})
    return {"access_token": access_token, "token_type": "bearer"}


@router.post("/register",
             response_model=schemas.User
             )
async def register(service: Annotated[UserService, Depends(UserService)],
                   user: schemas.UserCreate,
                   ) -> Any:
    """
    Register a new user.

    :param service: User service.
    :param user: User create schema.

    :return: Newly created user.
    """
    if service.get_by_username(user.username):
        return responses.JSONResponse(
            status_code=status.HTTP_409_CONFLICT,
            content={"message": f"Username {user.username} is already taken."}
        )
    if service.get_by_username(user.email):
        return responses.JSONResponse(
            status_code=status.HTTP_409_CONFLICT,
            content={"message": f"Email {user.email} is already taken."}
        )
    user.password = get_password_hash(password=user.password)
    user = service.create(user)
    if not user:
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                "message": "Could not register user."
            }
        )
    return user


@router.get("/me",
            response_model=schemas.User
            )
async def get_my_user(current_user: Annotated[schemas.User, Depends(get_current_user)]
                      ) -> Any:
    """
    Get currently authenticated user.

    :param current_user: Current user.

    :return: Current user.
    """
    return current_user
