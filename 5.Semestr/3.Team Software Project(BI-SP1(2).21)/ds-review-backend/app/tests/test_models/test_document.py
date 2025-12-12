import uuid

import pytest

import models
from models import DocumentState, DocumentType


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest

@pytest.fixture(scope="module")
def shared_uuid():
    return uuid.uuid4(), uuid.uuid4()


def test_create_document(db_session, shared_uuid):
    test_title = "How to win?"
    test_content = "Work hard."
    test_uuid, test_uuid_submission = shared_uuid
    db_obj = models.Document(uuid=test_uuid, uuid_submission=test_uuid_submission,
                             title=test_title, content=test_content,
                             doc_state=DocumentState.OPEN,
                             doc_type=DocumentType.PLAIN_TEXT)
    db_session.add(db_obj)
    db_session.commit()
    db_session.refresh(db_obj)
    assert db_obj is not None


def test_get_created_document(db_session, shared_uuid):
    test_title = "How to win?"
    test_content = "Work hard."
    test_uuid, test_uuid_submission = shared_uuid
    db_obj = db_session.get(models.Document, test_uuid)
    assert db_obj.uuid == test_uuid
    assert db_obj.uuid_submission == test_uuid_submission
    assert db_obj.title == test_title and db_obj.content == test_content
    assert db_obj.doc_type == DocumentType.PLAIN_TEXT
    assert db_obj.doc_state == DocumentState.OPEN
