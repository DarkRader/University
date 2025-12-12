import uuid
import pytest

import models
from models import DocumentState, DocumentType, EvaluationState


@pytest.fixture(scope="module")
def evaluation_uuid():
    return uuid.uuid4()


def test_create_evaluation(db_session, evaluation_uuid):
    document_uuid = uuid.uuid4()
    document = models.Document(
        uuid=document_uuid,
        uuid_submission=uuid.uuid4(),
        title="Test Document",
        content="Test Content",
        doc_state=DocumentState.OPEN,
        doc_type=DocumentType.PLAIN_TEXT,
    )
    db_session.add(document)

    user_uuid = uuid.uuid4()
    user = models.User(
        uuid=user_uuid,
        dsr_token="dsr-abf33dbd-0689-4314-a4b9-ea810c30bd75",
        username="GregorDan",
        password="wawgawgwalwgmna3827y37g2o",
        first_name="Dan",
        last_name="Gregrov",
        email="gregor.dan@cvut.cz",
        disabled=False,
    )
    db_session.add(user)

    db_obj = models.Evaluation(
        uuid=evaluation_uuid,
        state=EvaluationState.APPROVED,
        rating=10,
        document_uuid=document_uuid,
        user_uuid=user_uuid,
    )
    db_session.add(db_obj)
    db_session.commit()
    db_session.refresh(db_obj)
    assert db_obj is not None


# Test getting a created Evaluation instance
def test_get_created_evaluation(db_session, evaluation_uuid):
    db_obj = db_session.get(models.Evaluation, evaluation_uuid)
    assert db_obj is not None
    assert db_obj.state == EvaluationState.APPROVED
    assert db_obj.rating == 10

    document = db_session.get(models.Document, db_obj.document_uuid)
    assert document is not None
    assert document.title == "Test Document"
