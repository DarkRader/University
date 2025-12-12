"""Module for documents api integration tests."""
from uuid import UUID
import re

import pytest
from httpx import Response
from starlette.testclient import TestClient

from api.documents import router
import schemas
from models import DocumentState, DocumentType

# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest

UUID_REGEX = "[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-[089ab][0-9a-f]{3}-[0-9a-f]{12}"

DOCUMENT_CONTENTS_AND_TYPES = [
    (
        """<html><body>This is an HTML document content...</body></html>""",
        DocumentType.HTML
    ), (
        """
        {
            "title": "Test title",
            "content": {
                "arr": [1, 2, 3],
                "field": "value"
            }
        }""",
        DocumentType.JSON
    ), (
        """Plain text document content.""",
        DocumentType.PLAIN_TEXT
    ),
]


@pytest.fixture(scope="module")
def document_content_html():
    """Html document content."""
    return DOCUMENT_CONTENTS_AND_TYPES[0][0]


def get_location_from_post_response(response: Response) -> str:
    """Get location from request response."""
    return response.json()["location"]


def get_document_uuid_from_location(location: str) -> UUID:
    """Get uuids from location."""
    return UUID(re.findall(UUID_REGEX, location)[0])


def submit_document(client: TestClient, document_content: str, user_dsr_token_header: dict) -> UUID:
    """Submit document and check if correct location was sent."""
    response_submit = client.post(
        "/documents/submit",
        headers=user_dsr_token_header,
        json=document_content
    )
    assert response_submit.status_code == 201
    location = get_location_from_post_response(response_submit)
    assert location is not None
    uuid = get_document_uuid_from_location(location)
    assert uuid is not None
    return uuid


def get_document(
        client, uuid: UUID, document_content: str, document_type: DocumentType, user_authorization_header: dict
) -> schemas.Document:
    """Get document and check all parameters are as expected."""
    response_get = client.get(f"{router.prefix}/{uuid}", headers=user_authorization_header)
    assert response_get.status_code == 200
    document = schemas.Document(**response_get.json())
    assert document.uuid == uuid
    assert document.content == document_content
    assert document.doc_state == DocumentState.OPEN
    assert document.doc_type == document_type
    return document


@pytest.mark.parametrize("document_content, document_type", DOCUMENT_CONTENTS_AND_TYPES)
def test_submit_and_get_document(client, document_content, document_type, user):
    """Test submit document and get document."""
    uuid = submit_document(client, document_content, user.dsr_token)
    get_document(client, uuid, document_content, document_type, user.auth_header)


def test_get_all_documents(client, user):
    """Test get all documents."""
    response = client.get(router.prefix, headers=user.auth_header)
    assert response.status_code == 200


def test_submit_and_change_document(client, document_content_html, user):
    """Test submit document and change its status and title."""
    uuid = submit_document(client, document_content_html, user.dsr_token)
    update_state = DocumentState.CLOSED
    update_title = "Update title"
    response_update = client.put(f"{router.prefix}/{uuid}",
                                 headers=user.auth_header,
                                 json={
                                     "doc_state": update_state.value,
                                     "title": update_title
                                 }, )
    assert response_update.status_code == 200
    document_updated = schemas.Document(**response_update.json())
    assert document_updated.uuid == uuid
    assert document_updated.title == update_title
    assert document_updated.doc_state == update_state
