"""
Module for testing document service
"""
import pytest

from services import UserService
from schemas import UserCreate, UserUpdate
from ..utils import as_dict
from .test_user_create import user_create1, user_create2, user_create3, \
    user_create4, user_create5, user_create6


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest

@pytest.fixture()
def service_user(db_session) -> UserService:
    """Return UserService."""
    return UserService(db=db_session)


@pytest.fixture(scope="module")
def user_create() -> UserCreate:
    """Return create_schema_data for user."""
    return UserCreate(
        username="GregorDan",
        password="wawgawgwalwgmna3827y37g2o",
        first_name="Dan",
        last_name="Gregrov",
        email="gregor.dan@cvut.cz"
    )


@pytest.fixture(scope="module")
def user_update() -> UserUpdate:
    """Return update_schema_data for user."""
    return UserUpdate(
        first_name="Daniil",
        last_name="Gregorenko"
    )


def test_create_user(service_user):
    """
    Test for create method in UserService
    """
    obj = service_user.create(obj_in=user_create1())
    assert obj is not None


def test_get_created_user(service_user):
    """
    Test for get method in UserService
    """
    obj = service_user.create(obj_in=user_create2())
    assert obj is not None

    db_obj = service_user.get(obj.uuid)
    assert db_obj is not None


def test_get_created_user_by_username(service_user):
    """
    Test for get_by_username method in UserService
    """
    db_obj = service_user.get_by_username("GregorDan")
    assert db_obj is not None


def test_get_created_user_by_email(service_user):
    """
    Test for get_by_email method in UserService
    """
    db_obj = service_user.get_by_email("gregor.dan@cvut.cz")
    assert db_obj is not None


def test_get_created_user_by_dsr_token(service_user):
    """
    Test for get_by_dsr_token method in UserService
    """
    obj = service_user.create(obj_in=user_create6())
    assert obj is not None

    db_obj = service_user.get_by_dsr_token(obj.dsr_token)
    assert db_obj is not None


def test_delete_created_user(service_user):
    """
    Test for remove method in UserService
    """
    db_obj = service_user.create(obj_in=user_create3())
    assert db_obj is not None

    db_obj_removed = service_user.remove(db_obj.uuid)

    assert db_obj == db_obj_removed


def test_delete_nonexistent_user(service_user):
    """
    Test for remove method in UserService
    for nonexistent user
    """
    db_obj = service_user.create(obj_in=user_create4())
    assert db_obj is not None

    db_obj_removed = service_user.remove(db_obj.uuid)
    assert db_obj_removed is not None
    db_obj_removed = service_user.remove(db_obj.uuid)
    assert db_obj_removed is None
    db_obj_removed = service_user.remove(None)
    assert db_obj_removed is None


def test_update(service_user, user_update):
    """
    Test for update method in UserService
    """
    db_obj_created = service_user.create(obj_in=user_create5())

    db_obj_to_update = service_user.get(db_obj_created.uuid)
    db_obj_updated = service_user.update(db_obj_to_update.uuid,
                                         user_update)

    db_obj_updated_data = as_dict(db_obj_updated)

    assert db_obj_updated_data["first_name"] == user_update.first_name
    assert db_obj_updated_data["last_name"] == user_update.last_name

    for field, value in user_create5():
        if field not in user_update.dict():
            assert db_obj_updated_data[field] == value
