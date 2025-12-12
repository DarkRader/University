from uuid import UUID

from httpx import Response
from starlette.testclient import TestClient

from api.document_permission import router
from models import DocumentPermissionType
from schemas import DocumentPermissionCreate, DocumentPermission, DocumentPermissionUpdate
from .conftest import UserTesting
from .test_documents import submit_document


def create_document_permission(
        client: TestClient, document_uuid: UUID, user: UserTesting,
        permission_type: DocumentPermissionType,
) -> Response:
    permission_response = client.post(
        router.prefix,
        headers=user.auth_header,
        content=DocumentPermissionCreate(
            document_uuid=document_uuid,
            permission_type=permission_type,
            user_uuid=user.uuid
        ).json(exclude_unset=True)
    )
    return permission_response


def create_document_permission_and_validate(
        client: TestClient, document_uuid: UUID, user: UserTesting,
        permission_type: DocumentPermissionType,
) -> DocumentPermission:
    permission_response = create_document_permission(
        client, document_uuid, user, permission_type
    )
    assert permission_response.status_code == 201

    document_permission = DocumentPermission(**permission_response.json())
    assert document_permission is not None
    assert document_permission.document_uuid == document_uuid
    assert document_permission.user_uuid == user.uuid
    assert document_permission.permission_type == permission_type
    return document_permission


def test_create_document_permission_valid(
        client: TestClient, user: UserTesting, user_2: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    create_document_permission_and_validate(
        client, document_uuid, user_2, DocumentPermissionType.REVIEWER
    )


def test_create_second_document_permission_with_different_permission_type(
        client: TestClient, user: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission_response = create_document_permission(
        client, document_uuid, user, DocumentPermissionType.REVIEWER
    )
    assert permission_response.status_code == 201


def test_create_second_document_permission_with_same_permission_type(
        client: TestClient, user: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission_response = create_document_permission(
        client, document_uuid, user, DocumentPermissionType.REVIEWER
    )
    assert permission_response.status_code == 201


def test_get_document_permissions_as_a_submitter(
        client: TestClient, user: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission_response = client.get(
        f"{router.prefix}",
        headers=user.auth_header,
        params={
            "document_uuid": str(document_uuid),
            "user_uuid": str(user.uuid),
        }
    )
    assert permission_response.status_code == 200

    permission = DocumentPermission(**permission_response.json()[0])
    assert permission is not None
    assert permission.document_uuid == document_uuid
    assert permission.user_uuid == user.uuid
    assert permission.permission_type == DocumentPermissionType.SUBMITTER


def test_get_document_permissions_as_a_reviewer(
        client: TestClient, user: UserTesting, user_2: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    create_document_permission_and_validate(
        client, document_uuid, user_2, DocumentPermissionType.REVIEWER
    )
    permission_response = client.get(
        f"{router.prefix}",
        headers=user.auth_header,
        params={
            "document_uuid": str(document_uuid),
            "user_uuid": str(user_2.uuid),
        }
    )
    assert permission_response.status_code == 200

    permission = DocumentPermission(**permission_response.json()[0])
    assert permission is not None
    assert permission.document_uuid == document_uuid
    assert permission.user_uuid == user_2.uuid
    assert permission.permission_type == DocumentPermissionType.REVIEWER


def test_get_document_permissions_without_permission(
        client: TestClient, user: UserTesting, user_2: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission_response = client.get(
        f"{router.prefix}",
        headers=user.auth_header,
        params={
            "document_uuid": str(document_uuid),
            "user_uuid": str(user_2.uuid),
        }
    )
    assert permission_response.status_code == 200

    permissions = [DocumentPermission(**permission) for permission in permission_response.json()]
    assert permissions is not None
    assert len(permissions) == 0


def test_update_document_permission_valid(
        client: TestClient, user: UserTesting, user_2: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission = create_document_permission_and_validate(
        client, document_uuid, user_2, DocumentPermissionType.REVIEWER
    )
    permission_response = client.put(
        f"{router.prefix}/{permission.uuid}",
        headers=user_2.auth_header,
        content=DocumentPermissionUpdate(
            permission_type=DocumentPermissionType.SUBMITTER
        ).json(exclude_unset=True)
    )
    assert permission_response.status_code == 200

    updated_permission = DocumentPermission(**permission_response.json())
    assert updated_permission.uuid == permission.uuid
    assert updated_permission.document_uuid == permission.document_uuid == document_uuid
    assert updated_permission.permission_type == DocumentPermissionType.SUBMITTER


def test_delete_document_permission_valid(
        client: TestClient, user: UserTesting, user_2: UserTesting
) -> None:
    document_uuid = submit_document(client, "Document content",
                                    user.dsr_token)
    permission = create_document_permission_and_validate(
        client, document_uuid, user_2, DocumentPermissionType.REVIEWER
    )
    permission_response = client.delete(
        f"{router.prefix}/{permission.uuid}",
        headers=user_2.auth_header
    )
    assert permission_response.status_code == 200
