"""
API controllers for document permissions.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Body, Path, Query, responses

from api import utils
import schemas
import models
from api.user_authenticator import get_current_user
from services import DocumentPermissionService

router = APIRouter(
    prefix="/document_permissions",
    tags=[utils.fastapi_docs.DOCUMENT_PERMISSION_TAG["name"]]
)


@router.get("/",
            response_model=List[schemas.DocumentPermission],
            status_code=status.HTTP_200_OK)
async def get_document_permissions(
        service: Annotated[DocumentPermissionService, Depends(DocumentPermissionService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_uuid: Annotated[UUID | None, Query()] = None,
        user_uuid: Annotated[UUID | None, Query()] = None,
        permission_type: Annotated[models.DocumentPermissionType | None, Query()] = None,
) -> Any:
    """
    Get all document permissions for document with uuid equal to document_uuid.

    :param service: Document Permission service.
    :param user: Current user.
    :param document_uuid: uuid of the document.
    :param user_uuid: uuid of the user.
    :param permission_type: Type of the document permission.
    """
    if not any([document_uuid, user_uuid, permission_type]):
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                "message": "Invalid request. No query parameters provided."
            }
        )
    document_permissions = service.get_by_document_uuid_user_uuid_and_permission_type(
        document_uuid, user_uuid, permission_type, user
    )
    if document_permissions is None:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return document_permissions


@router.get("/{document_permission_uuid}",
            response_model=schemas.DocumentPermission,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_document_permission(
        service: Annotated[DocumentPermissionService, Depends(DocumentPermissionService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_permission_uuid: Annotated[UUID, Path()]
) -> Any:
    """
    Get document permission with uuid equal to document_permission_uuid.

    :param service: Document Permission service.
    :param user: Current user.
    :param document_permission_uuid: uuid of the document permission.
    """
    document_permission = service.get_document_permission(document_permission_uuid, user)
    if not document_permission:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT_PERMISSION,
                                            document_permission_uuid)
    return document_permission


@router.post("/",
             response_model=schemas.DocumentPermission,
             responses={
                 400: {"model": utils.Message,
                       "description": "Couldn't create document_permission."},
             },
             status_code=status.HTTP_201_CREATED,
             )
async def post_document_permission(
        service: Annotated[DocumentPermissionService, Depends(DocumentPermissionService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_permission: schemas.DocumentPermissionCreate
) -> Any:
    """
    Create document permission.

    :param service: Document Permission service.
    :param user: Current user.
    :param document_permission: Document Permission Create schema.
    """
    document_permission = service.create_document_permission(document_permission, user)
    if not document_permission:
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                "message": "Could not create document permission."
            }
        )
    return document_permission


@router.put("/{document_permission_uuid}",
            response_model=schemas.DocumentPermission,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_document_permission(
        service: Annotated[DocumentPermissionService, Depends(DocumentPermissionService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_permission_uuid: Annotated[UUID, Path()],
        document_permission: Annotated[schemas.DocumentPermissionUpdate, Body()]
) -> Any:
    """
    Update document permission with uuid equal to document_permission_uuid.

    :param service: Document Permission service.
    :param user: Current user.
    :param document_permission_uuid: uuid of the document_permission.
    :param document_permission: Document Permission Update schema.
    """
    updated_document_permission = service.update_document_permission(document_permission_uuid,
                                                                     document_permission, user)
    if not updated_document_permission:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT_PERMISSION,
                                            document_permission_uuid)
    return updated_document_permission


@router.delete("/{document_permission_uuid}",
               response_model=schemas.DocumentPermission,
               responses={
                   **utils.EntityNotFoundException.RESPONSE,
               },
               status_code=status.HTTP_200_OK)
async def delete_document_permission(
        service: Annotated[DocumentPermissionService, Depends(DocumentPermissionService)],
        user: Annotated[schemas.User, Depends(get_current_user)],
        document_permission_uuid: Annotated[UUID, Path()]
) -> Any:
    """Delete document permission with uuid equal to document_permission_uuid.

    :param service: Document Permission service.
    :param user: Current user.
    :param document_permission_uuid: uuid of the document permission.
    """
    deleted_document_permission = service.remove_document_permission(document_permission_uuid, user)
    if not deleted_document_permission:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT_PERMISSION,
                                            document_permission_uuid)
    return deleted_document_permission
