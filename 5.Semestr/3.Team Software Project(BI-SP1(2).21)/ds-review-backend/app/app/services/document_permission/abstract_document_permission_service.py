"""
This module defines an abstract base class AbstractDocumentPermissionService
that work with Document Permission
"""

from abc import ABC, abstractmethod
from uuid import UUID

from services import CrudServiceBase

import models
import schemas
import crud


class AbstractDocumentPermissionService(CrudServiceBase[
                                            models.DocumentPermission,
                                            crud.DocumentPermission,
                                            schemas.DocumentPermissionCreate,
                                            schemas.DocumentPermissionUpdate
                                        ], ABC):
    """
    This abstract class defines the interface for a document permission service
    that provides CRUD operations for a specific DocumentPermissionModel.
    """

    @abstractmethod
    def get_document_permission(self, uuid: UUID, user: models.User) -> \
            models.DocumentPermission | None:
        """
        Retrieve DocumentPermission from the database.
        :param uuid: the ID of the document permission to retrieve.
        :param user: the UserSchema for control permissions of the document.
        :returns: DocumentPermissionModel.
        """

    @abstractmethod
    def create_document_permission(self, doc_permission: schemas.DocumentPermissionCreate,
                                   user: schemas.User) \
            -> models.DocumentPermission | None:
        """
        Post DocumentPermission.
        :param doc_permission: DocumentPermissionCreate schema.
        :param user: the UserSchema for control permissions of the document.
        :returns DocumentPermission: the created document permission.
        """

    @abstractmethod
    def update_document_permission(self, uuid: UUID, obj_in: schemas.DocumentPermissionUpdate,
                                   user: models.User) \
            -> models.DocumentPermission | None:
        """
        Update DocumentPermission in the database.
        :param uuid: the ID of the document permission to update.
        :param obj_in: the updated document permission.
        :param user: the UserSchema for control permissions of the document.
        :returns DocumentPermissionModel: the updated document permission.
        """

    @abstractmethod
    def remove_document_permission(self, uuid: UUID | None, user: models.User) -> \
            models.DocumentPermission | None:
        """
        Delete DocumentPermission from the database.
        :param uuid: the ID of the document permission to delete.
        :param user: the UserSchema for control permissions of the document.
        :returns DocumentPermissionModel: the removed document permission.
        """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[models.DocumentPermission]:
        """
        Retrieves DocumentPermission instances with the given document_uuid.

        :param document_uuid: The UUID of the associated Document.
        :return: A list of DocumentPermission instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_permission_type_all(self, document_uuid: UUID,
                                                     permission_type:
                                                     models.DocumentPermissionType) -> \
            list[models.DocumentPermission]:
        """
        Retrieves all DocumentPermission instances with the given document UUID and permission type.

        :param document_uuid: The UUID of the associated Document.
        :param permission_type: The type of the DocumentPermission.
        :return: A list of DocumentPermission instances.
        """

    @abstractmethod
    def get_by_user_uuid_and_permission_type_all(self, user_uuid: UUID,
                                                 permission_type: models.DocumentPermissionType
                                                 ) -> list[models.DocumentPermission]:
        """
        Retrieves all DocumentPermission instances with the given user UUID and permission type.

        :param user_uuid: The UUID of the associated User.
        :param permission_type: The type of the DocumentPermission.
        :return: A list of DocumentPermission instances.
        """

    @abstractmethod
    def get_by_user_uuid_all(self, user_uuid: UUID) -> list[models.DocumentPermission]:
        """
        Retrieves DocumentPermission instances with the given user_uuid.

        :param user_uuid: The UUID of the associated User.
        :return: A list of DocumentPermission instances.
        """

    @abstractmethod
    def get_by_document_uuid_and_user_uuid(self, document_uuid: UUID, user_uuid: UUID
                                           ) -> models.DocumentPermission | None:
        """
        Retrieves DocumentPermission instances with the given document_uuid and user_uuid.

        :param user_uuid: The UUID of the associated User.
        :param document_uuid: The UUID of the associated Document.
        :return: A list of DocumentPermission instances.
        """

    @abstractmethod
    def get_by_document_uuid_user_uuid_and_permission_type(self, document_uuid: UUID | None,
                                                           user_uuid: UUID | None,
                                                           permission_type:
                                                           models.DocumentPermissionType | None,
                                                           user: schemas.User
                                                           ) -> list[models.DocumentPermission]:
        """
        Retrieves DocumentPermission instances with the given document_uuid,
        user_uuid and permission_type.

        :param user_uuid: The UUID of the associated User.
        :param document_uuid: The UUID of the associated Document.
        :param permission_type: The type of the DocumentPermission.
        :param user: the UserSchema for control permissions of the document.
        :return: A list of DocumentPermission instances.
        """
