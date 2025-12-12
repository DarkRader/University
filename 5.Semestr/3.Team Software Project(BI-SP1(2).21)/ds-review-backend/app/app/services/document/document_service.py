"""
This module defines class DocumentService that work with Document
"""
import logging
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from sqlalchemy import Row
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractDocumentService
from services.document.document_service_parser import DocumentServiceParser
from sqlalchemy.orm import Session

log = logging.getLogger(__name__)


class DocumentService(AbstractDocumentService):
    """
    Class DocumentService represent service that work with Document
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_permission_crud = crud.DocumentPermission(db)
        super().__init__(crud.Document(db))

    def get_document(self, uuid: UUID, user: schemas.User) -> models.Document | None:
        log.info(f"Retrieving document with UUID: {uuid}")
        document = self.crud.get(uuid)
        if document is None:
            log.warning(f"Document not found for UUID: {uuid}")
            return None
        # control permissions
        permission = self.document_permission_crud.get_by_document_uuid_and_user_uuid(
            uuid, user.uuid)

        if permission is None:
            log.warning(f"Unauthorized access to document with UUID: {uuid}")
            return None

        return document

    def get_all_documents(self, user: schemas.User) -> list[Row[models.Document]] | None:
        # control permissions
        permissions = self.document_permission_crud.get_by_user_uuid_all(user.uuid)

        all_documents = []

        for permission in permissions:
            all_documents.append(self.crud.get(permission.document_uuid))

        log.info(f"Fetching all documents associated with user {user.username}")
        return all_documents

    def remove_document(self, uuid: UUID | None, user: schemas.User) -> models.Document | None:
        log.info(f"Removing document with UUID: {uuid}")
        # control permissions
        permission = self.document_permission_crud.\
            get_by_document_uuid_user_uuid_and_permission_type(
                uuid, user.uuid, models.DocumentPermissionType.SUBMITTER)

        if permission is None:
            log.warning(f"Unauthorized removal of document with UUID: {uuid}")
            return None

        self.document_permission_crud.remove(permission.uuid)
        removed_document = self.crud.remove(uuid)
        if removed_document is None:
            log.warning(f"Failed to remove document with UUID: {uuid}")
        return removed_document

    def submit_document(self, payload: str, user: schemas.User) -> models.Document:
        parser = DocumentServiceParser()
        doc_type = parser.get_type(payload)
        title = parser.parse(payload, doc_type)

        log.debug(f"Parsed document type: {doc_type}, title: {title}")

        doc_create = schemas.DocumentCreate(
            title=title,
            doc_type=doc_type,
            content=payload
        )

        doc_in_db = self.crud.create(obj_in=doc_create)

        # create document permission
        if doc_in_db is not None:
            doc_permission_create = schemas.DocumentPermissionCreate(
                permission_type=models.DocumentPermissionType.SUBMITTER,
                document_uuid=doc_in_db.uuid,
                user_uuid=user.uuid
            )

            self.document_permission_crud.\
                create(doc_permission_create)
            log.info(f"Document created with UUID: {doc_in_db.uuid}")

        return doc_in_db

    def update_document(self, uuid: UUID,
                        obj_in: schemas.DocumentUpdate,
                        user: models.User) -> models.Document | None:
        log.info(f"Updating document with UUID: {uuid}")
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            log.warning(f"Document update failed: No document found with UUID: {uuid}")
            return None

        # control permissions
        permission = self.document_permission_crud.\
            get_by_document_uuid_user_uuid_and_permission_type(
                uuid, user.uuid, models.DocumentPermissionType.SUBMITTER)

        if permission is None:
            log.warning(f"Unauthorized update of document with UUID: {uuid}")
            return None

        document_update = schemas.utils.as_dict(obj_in)
        if obj_in.doc_state == models.DocumentState.CLOSED and \
                obj_to_update.doc_state == models.DocumentState.OPEN:
            document_update["closed_at"] = datetime.utcnow()

        if obj_in.doc_state == models.DocumentState.OPEN:
            document_update["closed_at"] = None

        updated_document = self.crud.update(db_obj=obj_to_update, obj_in=document_update)
        log.info(f"Document updated with UUID: {updated_document.uuid}")
        return updated_document

    def get_by_submission_uuid(self, document_uuid_submission: UUID) -> models.Document | None:
        log.info(f"Fetching document by submission UUID: {document_uuid_submission}")
        return self.crud.get_by_submission_uuid(document_uuid_submission)

    def get_by_state_all(self, doc_state: models.DocumentState) -> list[Type[models.Document]]:
        log.info(f"Fetching all documents with state: {doc_state}")
        return self.crud.get_by_state_all(doc_state)

    def get_by_state_multi(self, doc_state: models.DocumentState,
                           skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        log.info(f"Fetching documents with state: {doc_state}, skip: {skip}, limit: {limit}")
        return self.crud.get_by_state_multi(doc_state, skip, limit)

    def get_by_type_multi(self, doc_type: models.DocumentType,
                          skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        log.info(f"Fetching documents with type: {doc_type}, skip: {skip}, limit: {limit}")
        return self.crud.get_by_type_multi(doc_type, skip, limit)

    def get_by_type_all(self, doc_type: models.DocumentType) -> list[Type[models.Document]]:
        log.info(f"Fetching all documents with type: {doc_type}")
        return self.crud.get_by_type_all(doc_type)
