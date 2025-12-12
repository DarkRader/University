"""Module for evaluations api integration tests."""
from uuid import uuid4, UUID

import pytest
from starlette.testclient import TestClient

from api.evaluations import router
import schemas
from models import EvaluationState, DocumentPermissionType
from schemas import EvaluationCreate
from .conftest import UserTesting
from .test_document_permissions import create_document_permission_and_validate
from .test_documents import submit_document


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture(scope="module")
def evaluation_create_schema_approved():
    """Evaluation create schema."""
    return schemas.EvaluationCreate(
        document_uuid=uuid4(),
        rating=9,
        state=EvaluationState.APPROVED
    )


@pytest.fixture(scope="module")
def evaluation_create_schema_disapproved():
    """Evaluation create schema."""
    return schemas.EvaluationCreate(
        document_uuid=uuid4(),
        rating=2,
        state=EvaluationState.DISAPPROVED
    )


@pytest.fixture(scope="module")
def evaluation_update_schema():
    """Evaluation create schema."""
    return schemas.EvaluationUpdate(
        rating=8,
        state=EvaluationState.APPROVED,
    )


def create_evaluation(
        client: TestClient, evaluation_create_schema: EvaluationCreate,
        submitter: UserTesting, reviewer: UserTesting
) -> tuple[UUID, schemas.Evaluation | None]:
    """Create evaluation and return document_uuid and Evaluation schema if successful."""
    # submit document
    document_uuid = submit_document(client, "Document content",
                                    submitter.dsr_token)

    # grant permissions to reviewer
    create_document_permission_and_validate(
        client, document_uuid, reviewer, DocumentPermissionType.REVIEWER
    )

    # create evaluation
    evaluation_create_schema.document_uuid = document_uuid
    response_create = client.post(
        router.prefix,
        headers=reviewer.auth_header,
        content=evaluation_create_schema.json(exclude_unset=True)
    )
    return (
        document_uuid,
        schemas.Evaluation(**response_create.json()) if response_create.status_code == 201 else None
    )


def test_create_and_update_evaluation(
        client, evaluation_create_schema_disapproved, evaluation_update_schema, user, user_2
):
    """Create evaluation, update evaluation."""
    # create evaluation
    document_uuid, evaluation = create_evaluation(
        client, evaluation_create_schema_disapproved, submitter=user, reviewer=user_2
    )
    assert evaluation is not None
    assert evaluation.rating == evaluation_create_schema_disapproved.rating
    assert evaluation.state == evaluation_create_schema_disapproved.state

    # update evaluation
    response_update = client.put(
        f"{router.prefix}/{evaluation.uuid}",
        headers=user_2.auth_header,
        content=evaluation_update_schema.json(exclude_unset=True)
    )
    assert response_update.status_code == 200
    evaluation_updated = schemas.Evaluation(**response_update.json())
    assert evaluation_updated.uuid == evaluation.uuid
    assert evaluation_updated.document_uuid == document_uuid
    assert evaluation_updated.state == evaluation_update_schema.state
