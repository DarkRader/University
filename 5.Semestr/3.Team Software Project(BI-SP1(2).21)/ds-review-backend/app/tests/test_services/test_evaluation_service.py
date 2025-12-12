"""
Module for testing comment service
"""
from uuid import uuid4
from services import EvaluationService, DiscussionService, UserService

import pytest
import models
import schemas
from .test_user_create import user_create1, user_create2, user_create3, user_create4


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture()
def service_evaluation(db_session) -> EvaluationService:
    """Return EvaluationService."""
    return EvaluationService(db=db_session)


@pytest.fixture()
def service_user(db_session) -> UserService:
    """Return UserService."""
    return UserService(db=db_session)


@pytest.fixture()
def service_discussion(db_session) -> DiscussionService:
    """Return EvaluationService."""
    return DiscussionService(db=db_session)


def document_permission_create(document_uuid, user_uuid, permission_type) -> \
        schemas.DocumentPermissionCreate:
    """Return create_schema_data for document."""
    return schemas.DocumentPermissionCreate(
        permission_type=permission_type,
        document_uuid=document_uuid,
        user_uuid=user_uuid
    )


@pytest.fixture(scope="module")
def evaluation_update() -> schemas.EvaluationUpdate:
    """Return update_schema_data for evaluation."""
    return schemas.EvaluationUpdate(
        state=models.EvaluationState.APPROVED
    )


@pytest.fixture
def document_create() -> schemas.DocumentCreate:
    """Return document_create for document."""
    return schemas.DocumentCreate(
        title="title",
        doc_type=models.DocumentType.HTML,
        content="Test content"
    )


@pytest.fixture
def discussion_create() -> schemas.DiscussionCreate:
    """Return discussion_create for discussion."""
    return schemas.DiscussionCreate(
        document_uuid=uuid4()
    )


@pytest.fixture
def evaluation_create() -> schemas.EvaluationCreate:
    """Return evaluation_create for evaluation."""
    return schemas.EvaluationCreate(
        state=models.EvaluationState.DISAPPROVED,
        rating=6,
        document_uuid=uuid4()
    )


def create_evaluation(service_evaluation,
                      service_discussion,
                      document_create,
                      discussion_create,
                      evaluation_create,
                      user) -> models.Discussion:
    """
    Additional function for creating an evaluation
    """
    doc_in_db = service_evaluation.document_crud.create(document_create)
    service_evaluation.document_permission_crud.create(
        document_permission_create(doc_in_db.uuid, user.uuid,
                                   models.DocumentPermissionType.REVIEWER))
    discussion_create.document_uuid = doc_in_db.uuid
    evaluation_create.document_uuid = doc_in_db.uuid
    evaluation_in_db = service_evaluation.create_evaluation(evaluation_create, user)
    discussion_create.evaluation_uuid = evaluation_in_db.uuid
    discussion_in_db = service_discussion.create_discussion(discussion_create, user)
    assert discussion_in_db is not None
    assert evaluation_in_db is not None
    assert evaluation_in_db.document is not None
    assert evaluation_in_db.document_uuid is not None
    assert len(evaluation_in_db.discussion) != 0
    return evaluation_in_db


def test_create(service_evaluation,
                service_discussion,
                document_create,
                discussion_create,
                evaluation_create,
                service_user):
    """
    Test for create method in EvaluationService
    """
    user = service_user.create(obj_in=user_create1())
    create_evaluation(service_evaluation,
                      service_discussion,
                      document_create,
                      discussion_create,
                      evaluation_create,
                      user)


def test_create_with_invalid_rating(service_evaluation,
                                    document_create,
                                    discussion_create,
                                    evaluation_create,
                                    service_user):
    """
    Test for create method in EvaluationService
    """
    evaluation_create.rating = 11
    doc_in_db = service_evaluation.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    evaluation_create.document_uuid = doc_in_db.uuid
    user = service_user.create(obj_in=user_create2())
    evaluation_in_db = service_evaluation.create_evaluation(evaluation_create, user)
    assert evaluation_in_db is None


def test_get_created_evaluation(service_evaluation,
                                service_discussion,
                                document_create,
                                discussion_create,
                                evaluation_create,
                                service_user):
    """
    Test for get method in EvaluationService
    """
    user = service_user.create(obj_in=user_create3())
    evaluation_in_db = create_evaluation(service_evaluation,
                                         service_discussion,
                                         document_create,
                                         discussion_create,
                                         evaluation_create,
                                         user)

    db_obj = service_evaluation.get_evaluation(evaluation_in_db.uuid, user)
    assert db_obj is not None


def test_update(service_evaluation,
                service_discussion,
                document_create,
                discussion_create,
                evaluation_create,
                evaluation_update,
                service_user):
    """
    Test for update method in EvaluationService
    """
    user = service_user.create(obj_in=user_create4())
    evaluation_in_db = create_evaluation(service_evaluation,
                                         service_discussion,
                                         document_create,
                                         discussion_create,
                                         evaluation_create,
                                         user)

    db_obj_to_update = service_evaluation.get_evaluation(evaluation_in_db.uuid, user)
    db_obj_updated = service_evaluation.update_evaluation(db_obj_to_update.uuid,
                                                          evaluation_update, user)
