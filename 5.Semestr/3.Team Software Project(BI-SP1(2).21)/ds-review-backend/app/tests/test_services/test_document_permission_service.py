"""
Module for testing document permission service
"""
import pytest

from services import UserService, DocumentPermissionService
from models import DocumentType, DocumentPermissionType, DocumentPermission
from schemas import DocumentCreate, DocumentPermissionCreate, DocumentPermissionUpdate
from ..utils import as_dict
from .test_user_create import user_create1, user_create2, user_create3, user_create4, \
    user_create5, user_create6, user_create7


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture()
def service_document_permission(db_session) -> DocumentPermissionService:
    """Return DocumentPermissionService."""
    return DocumentPermissionService(db=db_session)


@pytest.fixture()
def service_user(db_session) -> UserService:
    """Return UserService."""
    return UserService(db=db_session)


@pytest.fixture(scope="module")
def document_create() -> DocumentCreate:
    """Return create_schema_data for document."""
    return DocumentCreate(
        title="Good code, bad code.",
        content="<h1>Write always a good code.</h1>",
        doc_type=DocumentType.HTML
    )


@pytest.fixture(scope="module")
def document_permission_update() -> DocumentPermissionUpdate:
    """Return update_schema_data for document_permission."""
    return DocumentPermissionUpdate(
        permission_type=DocumentPermissionType.REVIEWER,
    )


def document_permission_create(document_uuid, user_uuid, permission_type) -> \
        DocumentPermissionCreate:
    """Return create_schema_data for document_permission."""
    return DocumentPermissionCreate(
        permission_type=permission_type,
        document_uuid=document_uuid,
        user_uuid=user_uuid
    )


def create_document_permission(service_document_permission,
                               document_create,
                               user) -> DocumentPermission:
    """
    Additional function for creating a document_permission
    """
    doc_in_db = service_document_permission.document_crud.create(obj_in=document_create)
    permission_create = document_permission_create(doc_in_db.uuid, user.uuid,
                                                   DocumentPermissionType.SUBMITTER)
    obj = service_document_permission.create_document_permission(permission_create, user)
    assert obj is not None
    assert obj.document_uuid == doc_in_db.uuid
    assert obj.user_uuid == user.uuid
    return obj


def test_create_document_permission(service_document_permission, service_user, document_create):
    """
    Test for create method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create1())
    create_document_permission(service_document_permission, document_create, user)


def test_get_document_permission(service_document_permission, service_user, document_create):
    """
    Test for create method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create2())
    permission = create_document_permission(service_document_permission, document_create, user)

    db_obj = service_document_permission.get_document_permission(permission.uuid, user)
    assert db_obj is not None


def test_delete_created_document_permission(service_document_permission,
                                            service_user, document_create):
    """
    Test for remove method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create3())
    permission = create_document_permission(service_document_permission, document_create, user)

    db_obj = service_document_permission.get_document_permission(permission.uuid, user)
    db_obj_removed = service_document_permission.remove_document_permission(db_obj.uuid, user)

    assert db_obj == db_obj_removed


def test_delete_nonexistent_document_permission(service_document_permission,
                                                service_user, document_create):
    """
    Test for remove method in DocumentPermissionService
    for nonexistent document_permission
    """
    user = service_user.create(obj_in=user_create4())
    permission = create_document_permission(service_document_permission, document_create, user)

    db_obj = service_document_permission.get_document_permission(permission.uuid, user)
    assert db_obj is not None

    db_obj_removed = service_document_permission.remove_document_permission(db_obj.uuid, user)
    assert db_obj_removed is not None
    db_obj_removed = service_document_permission.remove_document_permission(db_obj.uuid, user)
    assert db_obj_removed is None
    db_obj_removed = service_document_permission.remove_document_permission(None, user)
    assert db_obj_removed is None


def test_update_document_permission(service_document_permission, service_user, document_create,
                                    document_permission_update):
    """
    Test for update method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create5())
    permission = create_document_permission(service_document_permission, document_create, user)

    db_obj_to_update = service_document_permission.get_document_permission(permission.uuid, user)
    db_obj_updated = service_document_permission. \
        update_document_permission(db_obj_to_update.uuid,
                                   document_permission_update,
                                   user)

    # only for testing
    document_permission_update.granted_at = db_obj_updated.granted_at

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in document_permission_update:
        assert db_obj_updated_data[field] == value


def test_get_document_uuid_and_user_uuid(service_document_permission,
                                         service_user, document_create):
    """
    Test for get_document_uuid_and_user_uuid method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create6())
    permission = create_document_permission(service_document_permission, document_create, user)

    test_permission = service_document_permission. \
        get_by_document_uuid_and_user_uuid(permission.document_uuid,
                                           user.uuid)

    assert permission == test_permission


def test_get_by_document_uuid_user_uuid_and_permission_type(service_document_permission,
                                                            service_user, document_create):
    """
    Test for get_by_document_uuid_user_uuid_and_permission_type method in DocumentPermissionService
    """
    user = service_user.create(obj_in=user_create7())
    permission = create_document_permission(service_document_permission, document_create, user)

    test_permissions = service_document_permission. \
        get_by_document_uuid_user_uuid_and_permission_type(permission.document_uuid, user.uuid,
                                                           DocumentPermissionType.SUBMITTER, user)

    assert permission == test_permissions[0]

    test_permissions_reviewer = service_document_permission. \
        get_by_document_uuid_user_uuid_and_permission_type(permission.document_uuid, user.uuid,
                                                           DocumentPermissionType.REVIEWER, user)

    assert test_permissions_reviewer == []
