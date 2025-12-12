"""
This module defines the CRUD operations for the DocumentPermission model, including an
abstract base class (AbstractCRUDDocumentPermission) and
a concrete implementation (CRUDDocumentPermission)
using SQLAlchemy.
"""
from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID

from sqlalchemy.orm import Session

import models
import schemas

from crud import CRUDBase


class AbstractCRUDDocumentPermission(CRUDBase[
                                         models.DocumentPermission,
                                         schemas.DocumentPermissionCreate,
                                         schemas.DocumentPermissionUpdate
                                     ], ABC):
    """
    Abstract class for CRUD operations specific to the DocumentPermission model.
    It extends the generic CRUDBase class and defines additional abstract methods
    for querying and manipulating DocumentPermission instances.
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
    def get_by_document_uuid_user_uuid_and_permission_type(self, document_uuid: UUID,
                                                           user_uuid: UUID,
                                                           permission_type:
                                                           models.DocumentPermissionType
                                                           ) -> \
            models.DocumentPermission | None:
        """
        Retrieves DocumentPermission instances with the given document_uuid,
        user_uuid and permission_type.

        :param user_uuid: The UUID of the associated User.
        :param document_uuid: The UUID of the associated Document.
        :param permission_type: The type of the DocumentPermission.
        :return: A list of DocumentPermission instances.
        """


class CRUDDocumentPermission(AbstractCRUDDocumentPermission):
    """
    Concrete class for CRUD operations specific to the DocumentPermission model.
    It extends the abstract AbstractCRUDDocumentPermission class and implements the required methods
    for querying and manipulating DocumentPermission instances.
    """

    def __init__(self, db: Session):
        super().__init__(models.DocumentPermission, db)

    def get_by_document_uuid_all(self, document_uuid: UUID
                                 ) -> list[Type[models.DocumentPermission]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid) \
            .all()

    def get_by_document_uuid_and_permission_type_all(self, document_uuid: UUID,
                                                     permission_type: models.DocumentPermissionType
                                                     ) -> list[Type[models.DocumentPermission]]:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid,
                    self.model.permission_type == permission_type) \
            .all()

    def get_by_user_uuid_all(self, user_uuid: UUID) -> list[Type[models.DocumentPermission]]:
        return self.db.query(self.model) \
            .filter(self.model.user_uuid == user_uuid) \
            .all()

    def get_by_user_uuid_and_permission_type_all(self, user_uuid: UUID,
                                                 permission_type: models.DocumentPermissionType
                                                 ) -> list[Type[models.DocumentPermission]]:
        return self.db.query(self.model) \
            .filter(self.model.user_uuid == user_uuid,
                    self.model.permission_type == permission_type) \
            .all()

    def get_by_document_uuid_and_user_uuid(self, document_uuid: UUID, user_uuid: UUID
                                           ) -> Type[models.DocumentPermission] | None:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid,
                    self.model.user_uuid == user_uuid) \
            .first()

    def get_by_document_uuid_user_uuid_and_permission_type(self, document_uuid: UUID,
                                                           user_uuid: UUID,
                                                           permission_type:
                                                           models.DocumentPermissionType
                                                           ) -> \
            Type[models.DocumentPermission] | None:
        return self.db.query(self.model) \
            .filter(self.model.document_uuid == document_uuid,
                    self.model.user_uuid == user_uuid,
                    self.model.permission_type == permission_type) \
            .first()
