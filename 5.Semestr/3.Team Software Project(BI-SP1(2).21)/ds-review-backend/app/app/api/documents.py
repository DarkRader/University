"""
API controllers for documents.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Body, Path, Header

from api import utils
import schemas
from api.user_authenticator import get_current_user
from schemas import User
from services import DocumentService, UserService

router = APIRouter(
    prefix="/documents",
    tags=[utils.fastapi_docs.DOCUMENT_TAG["name"]]
)


@router.post("/submit",
             status_code=status.HTTP_201_CREATED)
async def submit_document(document_service: Annotated[DocumentService, Depends(DocumentService)],
                          user_service: Annotated[UserService, Depends(UserService)],
                          content: Annotated[str, Body(description="Document content",
                                                       media_type="text/plain")],
                          x_dsr_token: Annotated[str, Header()]
                          ) -> Any:
    """
    Submit document from DSW, save it to db and return its submitter uuid.

    :param document_service: Document service.
    :param user_service: User service.
    :param content: Document content.
    :param x_dsr_token: Request headers x-dsr-token.

    :return: Fastapi response with status code and location of submitter view for document.
    """
    return utils.DSWRequest(document_service, user_service, content, x_dsr_token).validate_and_submit_document()


@router.get("/",
            response_model=List[schemas.Document],
            status_code=status.HTTP_200_OK)
async def get_all_documents(service: Annotated[DocumentService, Depends(DocumentService)],
                            user: Annotated[User, Depends(get_current_user)],
                            ) -> Any:
    """
    Get all documents from database.

    :param service: Document service.
    :param user: Current user.

    :return: List of all documents or None if there are no documents in db.
    """
    return service.get_all_documents(user)


@router.get("/{document_uuid}",
            response_model=schemas.Document,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_document(service: Annotated[DocumentService, Depends(DocumentService)],
                       user: Annotated[User, Depends(get_current_user)],
                       document_uuid: Annotated[UUID, Path()]) -> Any:
    """
    Get document by its uuid.

    :param service: Document service.
    :param user: Current user.
    :param document_uuid: uuid of the document.

    :return: Document with uuid equal to document_uuid
             or None if no such document exists.
    """
    doc = service.get_document(document_uuid, user)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc


@router.put("/{document_uuid}",
            response_model=schemas.Document,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_document(service: Annotated[DocumentService, Depends(DocumentService)],
                          user: Annotated[User, Depends(get_current_user)],
                          document_uuid: Annotated[UUID, Path()],
                          document: Annotated[schemas.DocumentUpdate, Body()]) -> Any:
    """
    Update document with uuid equal to document_uuid.

    :param service: Document service.
    :param user: Current user.
    :param document_uuid: uuid of the document.
    :param document: DocumentUpdate schema.
    """
    doc = service.update_document(document_uuid, document, user)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc


@router.delete("/{document_uuid}",
               response_model=schemas.DocumentSubmitter,
               responses={
                   **utils.EntityNotFoundException.RESPONSE,
               },
               status_code=status.HTTP_200_OK)
async def delete_document(service: Annotated[DocumentService, Depends(DocumentService)],
                          user: Annotated[User, Depends(get_current_user)],
                          document_uuid: Annotated[UUID, Path()]) -> Any:
    """Delete document with uuid equal to document_uuid.

    :param service: Document service.
    :param user: Current user.
    :param document_uuid: uuid of the document.
    """
    doc = service.remove_document(document_uuid, user)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc
