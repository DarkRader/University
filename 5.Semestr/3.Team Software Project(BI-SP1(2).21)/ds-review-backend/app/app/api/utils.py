"""Utils for API."""
from enum import Enum
from uuid import UUID

from fastapi import status, Request, responses
from fastapi.responses import Response
from pydantic import BaseModel

from core import settings
from services import DocumentService, UserService


class Message(BaseModel):
    """Model for response message."""
    message: str


class Entity(Enum):
    """Enum for entity names."""
    USER = "User"
    DOCUMENT = "Document"
    DOCUMENT_PERMISSION = "DocumentPermission"
    DISCUSSION = "Discussion"
    COMMENT = "Comment"
    EVALUATION = "Evaluation"


# pylint: disable=unused-argument
# reason: Exception handlers require request and exception parameter.

def get_exception_response_detail(status_code: int, desc: str) -> dict:
    """Get exception response detail for openAPI documentation.

    :param status_code: Status code of the exception.
    :param desc: Description of the exception.

    :return dict: Exception response detail.
    """
    return {
        status_code: {
            "model": Message,
            "description": desc
        }
    }


class MethodNotAllowedException(Exception):
    """Exception for not allowed methods."""
    STATUS_CODE = status.HTTP_405_METHOD_NOT_ALLOWED
    DESCRIPTION = "Method not allowed."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)

    def __init__(self, entity: Entity):
        self.entity = entity


def method_not_allowed_exception_handler(
        request: Request, exc: MethodNotAllowedException
) -> responses.JSONResponse:
    """Exception handler for MethodNotAllowedException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": f"Method {request.method} is not allowed for entity {exc.entity.value}"
        },
    )


class EntityNotFoundException(Exception):
    """Exception for when entity is not found in database."""
    STATUS_CODE = status.HTTP_404_NOT_FOUND
    DESCRIPTION = "Entity not found."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)

    def __init__(self, entity: Entity, entity_uuid: UUID):
        self.entity = entity
        self.entity_uuid = entity_uuid


def entity_not_found_exception_handler(
        request: Request, exc: EntityNotFoundException
) -> responses.JSONResponse:
    """Exception handler for EntityNotFoundException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": f"Entity {exc.entity.value} with uuid {exc.entity_uuid} was not found."
        },
    )


class NotImplementedException(Exception):
    """Exception for when a functionality is not yet implemented."""
    STATUS_CODE = status.HTTP_501_NOT_IMPLEMENTED
    DESCRIPTION = "Method not implemented."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)


def not_implemented_exception_handler(
        request: Request, exc: NotImplementedException
) -> responses.JSONResponse:
    """Exception handler for NotImplementedException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": exc.DESCRIPTION
        },
    )


# pylint: enable=unused-argument


# pylint: disable=too-few-public-methods
# reason: no more public methods needed.
class DSWRequest:
    """Validate request token, get data from request and return response to DSW."""

    def __init__(self, document_service: DocumentService, user_service: UserService,
                 content: str, x_dsr_token: str):
        self.document_service = document_service
        self.user_service = user_service
        self.content = content
        self.x_dsr_token = x_dsr_token

    def validate_and_submit_document(self) -> Response:
        """Validate request token, get data from request and return response to DSW."""
        if not self.__validate_token():
            return responses.PlainTextResponse(
                status_code=status.HTTP_401_UNAUTHORIZED,
                content=f"""
                Unauthorized submission request. Invalid dsr token {self.x_dsr_token}.
                Register on this site and copy your DSR_TOKEN to DSWizard -> Edit profile ->
                Submission Settings -> token.
                If you don't see this field, contact your DSW administrator.
                """  # TODO - better message
            )
        self.__get_request_data()
        return responses.JSONResponse(
            status_code=status.HTTP_201_CREATED,
            headers={
                "Location": self.location,
            },
            content={
                "location": self.location,
            }
        )

    def __validate_token(self) -> bool:
        """
        Validates DSR token.

        :return: True if token valid, False otherwise.
        """
        user = self.user_service.get_by_dsr_token(self.x_dsr_token)
        if not user:
            return False
        return True

    def __get_request_data(self) -> None:
        """
        Get data from DSW request.

        :return: None.
        """
        self.document = self.document_service. \
            submit_document(str(self.content),
                            self.user_service.get_by_dsr_token(self.x_dsr_token))
        self.location = f"{settings.FRONTEND_SUBMITTER_VIEW_PATH}{self.document.uuid}"


class FastApiDocs:
    """Information for fastapi documentation."""
    NAME = "Data Stewardship Review"
    DESCRIPTION = """Data Stewardship Review API is a **REST API** that offers you an access to
    our application's documents, discussions, comments and more!"""
    VERSION = "1.0.0"
    USER_TAG = {
        "name": "users",
        "description": "Operations with users.",
    }
    DOCUMENT_TAG = {
        "name": "documents",
        "description": "Operations with documents. The POST operation is customized to "
                       "work with sharing a document from DSW.",
    }
    DOCUMENT_PERMISSION_TAG = {
        "name": "document_permissions",
        "description": "Operations with document permissions.",
    }
    DISCUSSION_TAG = {
        "name": "discussions",
        "description": "Operations with discussions.",
    }
    COMMENT_TAG = {
        "name": "comments",
        "description": "Operations with comments. POST method can also create a Discussion.",
    }
    EVALUATION_TAG = {
        "name": "evaluations",
        "description": "Operations with evaluations.",
    }

    def get_tags_metadata(self):
        """Get tags metadata."""
        return [
            self.USER_TAG,
            self.DOCUMENT_TAG,
            self.DOCUMENT_PERMISSION_TAG,
            self.DISCUSSION_TAG,
            self.COMMENT_TAG,
            self.EVALUATION_TAG,
        ]


fastapi_docs = FastApiDocs()

# pylint: enable=too-few-public-methods
