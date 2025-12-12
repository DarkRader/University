"""
This module defines class DocumentPermissionService that work with DocumentPermission
"""
import logging
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractDocumentPermissionService
from sqlalchemy.orm import Session

log = logging.getLogger(__name__)


class DocumentPermissionService(AbstractDocumentPermissionService):
    """
    Class DocumentPermissionService represent service that work with Document Permission
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_crud = crud.Document(db)
        super().__init__(crud.DocumentPermission(db))

    def get_document_permission(self, uuid: UUID, user: models.User) -> models.Document | None:
        log.info(f"Retrieving document permission with UUID {uuid} for user {user.username}")
        document_permission = self.crud.get(uuid)
        if document_permission.user_uuid != user.uuid:
            log.warning(f"Document permission with UUID {uuid} doesn't belong to user {user.username}")
            return None
        return document_permission

    def create_document_permission(self, doc_permission: schemas.DocumentPermissionCreate,
                                   user: schemas.User) \
            -> models.DocumentPermission | None:
        log.info(f"Creating document permission for document with UUID "
                 f"{doc_permission.document_uuid} for user with UUID {doc_permission.user_uuid}")
        stored_permission = self.crud.get_by_document_uuid_and_user_uuid(
            doc_permission.document_uuid, doc_permission.user_uuid
        )
        if stored_permission is not None:
            log.warning(f"Document permission for document with UUID "
                        f"{doc_permission.document_uuid} and for user with UUID "
                        f"{doc_permission.user_uuid} already exists! And is of type "
                        f"{doc_permission.permission_type}")
        if doc_permission.user_uuid != user.uuid:
            log.warning(f"User with UUID {user.uuid} cannot create a document permission "
                        f"for user with uuid {doc_permission.user_uuid}")
            return None
        return self.crud.create(doc_permission)

    def update_document_permission(self, uuid: UUID, obj_in: schemas.DocumentPermissionUpdate,
                                   user: models.User) \
            -> models.DocumentPermission | None:
        log.info(f"Updating document permission with UUID {uuid}")
        obj_to_update = self.crud.get(uuid)
        if obj_to_update is None or obj_to_update.user_uuid != user.uuid:
            log.warning(f"Couldn't update document permission with UUID {uuid}.")
            return None
        return self.crud.update(db_obj=obj_to_update, obj_in=obj_in)

    def remove_document_permission(self, uuid: UUID | None, user: models.User) \
            -> models.DocumentPermission | None:
        log.info(f"Removing document permission with UUID {uuid}")
        document_permission = self.crud.get(uuid)
        if document_permission is not None and document_permission.user_uuid != user.uuid:
            log.warning(f"Couldn't remove document permission with UUID {uuid}.")
            return None
        return self.crud.remove(uuid)

    def get_by_document_uuid_all(self, document_uuid: UUID) -> \
            list[Type[models.DocumentPermission]]:
        log.info(f"Retrieving all document permissions for document with UUID {document_uuid}")
        return self.crud.get_by_document_uuid_all(document_uuid)

    def get_by_document_uuid_and_permission_type_all(self, document_uuid: UUID,
                                                     permission_type:
                                                     models.DocumentPermissionType) -> \
            list[Type[models.DocumentPermission]]:
        log.info(f"Retrieving all document permissions for document with UUID {document_uuid} "
                 f"and permission type {permission_type}")
        return self.crud.get_by_document_uuid_and_permission_type_all(document_uuid,
                                                                      permission_type)

    def get_by_user_uuid_and_permission_type_all(self, user_uuid: UUID,
                                                 permission_type: models.DocumentPermissionType
                                                 ) -> list[Type[models.DocumentPermission]]:
        log.info(f"Retrieving all document permissions for user with UUID {user_uuid} "
                 f"and permission type {permission_type}")
        return self.crud.get_by_user_uuid_and_permission_type_all(user_uuid, permission_type)

    def get_by_user_uuid_all(self, user_uuid: UUID) -> list[Type[models.DocumentPermission]]:
        log.info(f"Retrieving all document permissions for user with UUID {user_uuid}")
        return self.crud.get_by_user_uuid_all(user_uuid)

    def get_by_document_uuid_and_user_uuid(self, document_uuid: UUID, user_uuid: UUID
                                           ) -> Type[models.DocumentPermission]:
        log.info(f"Retrieving all document permissions for document with UUID {document_uuid} "
                 f"and user with UUID {user_uuid}")
        return self.crud.get_by_document_uuid_and_user_uuid(document_uuid, user_uuid)

    def get_by_document_uuid_user_uuid_and_permission_type(self, document_uuid: UUID,
                                                           user_uuid: UUID,
                                                           permission_type:
                                                           models.DocumentPermissionType,
                                                           user: schemas.User
                                                           ) -> \
            list[Type[models.DocumentPermission]]:
        if all([document_uuid, user_uuid, permission_type]):
            log.info(f"Retrieving all document permissions for document with UUID {document_uuid} "
                     f"and user with UUID {user_uuid} and permission type {permission_type}")
            permission = self.crud.get_by_document_uuid_user_uuid_and_permission_type(
                document_uuid, user_uuid, permission_type)
            return [permission] if permission is not None else []
        elif all([document_uuid, user_uuid]):
            permission = self.get_by_document_uuid_and_user_uuid(document_uuid, user_uuid)
            return [permission] if permission is not None else []
        elif all([document_uuid, permission_type]):
            return self.get_by_document_uuid_and_permission_type_all(document_uuid,
                                                                     permission_type)
        elif all([user_uuid, permission_type]):
            return self.get_by_user_uuid_and_permission_type_all(user_uuid, permission_type)
        elif document_uuid:
            return self.get_by_document_uuid_all(document_uuid)
        elif user_uuid:
            return self.get_by_user_uuid_all(user_uuid)
        elif permission_type:
            return self.get_by_user_uuid_and_permission_type_all(user.uuid, permission_type)
        log.warning(f"Method `get_by_document_uuid_user_uuid_and_permission_type` "
                    f"called with all arguments None.")
        return []
