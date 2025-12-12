import pytest
from datetime import datetime
from uuid import uuid4

import schemas
from models.document_permission import DocumentPermissionType


@pytest.fixture(scope="module")
def document_permission_schema() -> schemas.DocumentPermission:
    return schemas.DocumentPermission(
        uuid=uuid4(),
        document_uuid=uuid4(),
        user_uuid=uuid4(),
        granted_at=datetime.utcnow(),
        permission_type=DocumentPermissionType.SUBMITTER
    )


def test_document_permission_to_dict(document_permission_schema):
    """Check if document permission is correctly converted to dictionary.

    :param document_permission_schema: DocumentPermission schema.
    """
    res_dict = document_permission_schema.dict()

    assert res_dict["uuid"] == document_permission_schema.uuid
    assert res_dict["document_uuid"] == document_permission_schema.document_uuid
    assert res_dict["user_uuid"] == document_permission_schema.user_uuid
    assert res_dict["granted_at"] == document_permission_schema.granted_at
    assert res_dict["permission_type"] == document_permission_schema.permission_type
