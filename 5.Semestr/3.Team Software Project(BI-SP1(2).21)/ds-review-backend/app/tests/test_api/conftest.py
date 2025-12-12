import json

import pytest
from starlette.testclient import TestClient

from schemas import UserCreate, User
from api.users import router


class UserTesting:

    def __init__(self, client: TestClient, user_create: UserCreate):
        self.dsr_token, self.uuid = self.__create_user(client, user_create)
        self.auth_header: dict = self.__authorize(client, user_create)

    @staticmethod
    def __create_user(client: TestClient, user_create: UserCreate):
        """Register user and return its header with dsr-token"""
        response_register = client.post(f"{router.prefix}/register",
                                        content=user_create.json(exclude_unset=True))
        assert response_register.status_code == 200
        user = User(**json.loads(response_register.content.decode("utf-8")))
        return {"x-dsr-token": user.dsr_token}, user.uuid

    def __authorize(self, client: TestClient, user_create: UserCreate):
        """Login user and return header for authorization"""
        response_login = client.post(f"{router.prefix}/login", data=self.__get_login_credentials(user_create))
        assert response_login.status_code == 200
        token_data = json.loads(response_login.content.decode("utf-8"))
        assert "access_token" in token_data
        access_token = token_data["access_token"]
        return dict({"Authorization": f"Bearer {access_token}"})

    @staticmethod
    def __get_login_credentials(user_create: UserCreate):
        return {"username": user_create.username, "password": user_create.password}


@pytest.fixture(scope="module")
def user(client: TestClient) -> UserTesting:
    user_create = UserCreate(
        username="GregorDan",
        password="Test password",
        first_name="Dan",
        last_name="Gregrov",
        email="gregor.dan@cvut.cz"
    )
    return UserTesting(client, user_create)


@pytest.fixture(scope="module")
def user_2(client: TestClient) -> UserTesting:
    user_create = UserCreate(
        username="TomAdAr",
        password="super_secret_password",
        first_name="Prvni jmeno",
        last_name="Posledni jmeno",
        email="tomadar.asamtem@cvut.cz"
    )
    return UserTesting(client, user_create)
