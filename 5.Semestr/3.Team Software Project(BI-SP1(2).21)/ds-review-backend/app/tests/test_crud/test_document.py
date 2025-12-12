"""
Module for testing document crud
"""

import pytest
from fastapi.encoders import jsonable_encoder

import crud
from schemas import DocumentCreate, DocumentUpdate
from models import DocumentType, DocumentState
from ..utils import as_dict


# Using fixtures as variables is a standard for pytest
# pylint: disable=redefined-outer-name


@pytest.fixture()
def document_crud(db_session) -> crud.Document:
    """Return document crud."""
    return crud.Document(db=db_session)


@pytest.fixture(scope="module")
def document_create() -> DocumentCreate:
    """Return new document."""
    return DocumentCreate(
        title="Good code, bad code.",
        content="<h1>Write always a good code.</h1>",
        doc_type=DocumentType.HTML
    )


@pytest.fixture(scope="module")
def document_update() -> DocumentUpdate:
    """Return update_schema_data for document."""
    return DocumentUpdate(
        title="Message for all coders in the world.",
        doc_state=DocumentState.CLOSED
    )


def test_create_document(document_crud, document_create):
    """test creating document"""
    obj = document_crud.create(obj_in=document_create)
    assert obj is not None


def test_get_created_document(document_crud, document_create):
    """test getting created document"""
    obj = document_crud.create(obj_in=document_create)
    db_obj = document_crud.get(obj.uuid)
    assert db_obj is not None


def test_delete_created_document(document_crud, document_create):
    """test deleting created document"""
    db_obj = document_crud.create(obj_in=document_create)
    db_obj_removed = document_crud.remove(db_obj.uuid)

    assert db_obj == db_obj_removed


def test_create_delete_create_of_same_object(document_crud, document_create):
    """test create, delete, create of same object"""
    db_obj_created = document_crud.create(obj_in=document_create)
    db_obj_removed = document_crud.remove(db_obj_created.uuid)

    recreate_schema = DocumentCreate(**jsonable_encoder(db_obj_removed))
    db_obj_recreated = document_crud.create(recreate_schema)

    db_obj_data = as_dict(db_obj_recreated)
    assert db_obj_data is not None

    for field, value in recreate_schema:
        assert db_obj_data[field] == value


def test_remove_nonexistent_object(document_crud, document_create):
    """test removing nonexistent object"""
    db_obj = document_crud.create(obj_in=document_create)
    db_obj_removed = document_crud.remove(db_obj.uuid)
    assert db_obj_removed is not None
    db_obj_removed = document_crud.remove(db_obj.uuid)
    assert db_obj_removed is None
    db_obj_removed = document_crud.remove(None)
    assert db_obj_removed is None


def test_update(document_crud, document_create, document_update):
    """test updating document"""
    db_obj_created = document_crud.create(obj_in=document_create)

    db_obj_to_update = document_crud.get(db_obj_created.uuid)
    db_obj_updated = document_crud.update(db_obj=db_obj_to_update,
                                          obj_in=document_update)

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in document_update:
        assert db_obj_updated_data[field] == value
    for field, value in document_create:
        if field not in document_update.dict():
            assert db_obj_updated_data[field] == value



def test_create_with_create_scheme_with_defaults(document_crud, document_create):
    """test create with create scheme with defaults"""
    obj_in = DocumentCreate(title=document_create.title,
                            content=document_create.content,
                            doc_type=document_create.doc_type)
    created_obj = document_crud.create(obj_in)
    document_crud.remove(created_obj.uuid)


def test_get_by_public_uuid(document_crud, document_create):
    """Testing getting document by public uuid."""
    document = document_crud.create(obj_in=document_create)
    assert document_crud.get_by_submission_uuid(document.uuid_submission) is not None


def test_get_by_state(document_crud, document_create):
    """Testing updating document state and then getting that document by its state."""
    document = document_crud.create(obj_in=document_create)
    document_crud.update(db_obj=document, obj_in={"doc_state": DocumentState.CLOSED})
    closed_documents = document_crud.get_by_state_all(DocumentState.CLOSED)
    open_documents = document_crud.get_by_state_all(DocumentState.OPEN)
    assert len(closed_documents) != 0
    assert any(closed_document.uuid == document.uuid for closed_document in closed_documents)
    assert not any(closed_document.uuid == document.uuid for closed_document in open_documents)
