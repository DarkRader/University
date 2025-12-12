"""
Package for Services.
"""
from .service_base import AbstractCRUDService, CrudServiceBase
from .document.abstract_document_service import AbstractDocumentService
from .discussion.abstract_discussion_service import AbstractDiscussionService
from .comment.abstract_comment_service import AbstractCommentService
from .evaluation.abstract_evaluation_service import AbstractEvaluationService
from .user.abstract_user_service import AbstractUserService
from .document_permission.abstract_document_permission_service \
    import AbstractDocumentPermissionService
from .document.document_service import DocumentService
from .discussion.discussion_service import DiscussionService
from .comment.comment_service import CommentService
from .evaluation.evaluation_service import EvaluationService
from .user.user_service import UserService
from .document_permission.document_permission_service import DocumentPermissionService

__all__ = [
    "AbstractCRUDService", "CrudServiceBase", "AbstractDocumentService",
    "AbstractCommentService", "AbstractDiscussionService", "AbstractEvaluationService",
    "AbstractUserService", "AbstractDocumentPermissionService", "DocumentService",
    "DiscussionService", "CommentService", "EvaluationService", "UserService",
    "DocumentPermissionService"
]
