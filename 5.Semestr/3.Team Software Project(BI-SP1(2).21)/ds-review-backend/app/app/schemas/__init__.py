"""Shortcuts to easily import schemes."""
from .comment import Comment, CommentCreate, CommentUpdate, CommentInDB
from .discussion import Discussion, DiscussionCreate, DiscussionUpdate, DiscussionInDB, Crosslink
from .comment_and_discussion import CommentAndDiscussionCreate
from .document import Document, DocumentSubmitter, DocumentCreate, \
    DocumentUpdate, DocumentInDB
from .user import User, UserCreate, UserUpdate, UserInDB, Token, TokenData
from .utils import as_dict
from .evaluation import Evaluation, EvaluationCreate, EvaluationUpdate, EvaluationInDB
from .user import User, UserCreate, UserUpdate, UserUpdatePassword, UserInDB
from .document_permission import DocumentPermission, DocumentPermissionCreate, \
    DocumentPermissionUpdate, DocumentPermissionInDB

__all__ = [
    "Document", "DocumentSubmitter", "DocumentCreate", "DocumentUpdate",
    "DocumentInDB",
    "Discussion", "DiscussionCreate", "DiscussionUpdate", "DiscussionInDB", "Crosslink",
    "Comment", "CommentCreate", "CommentUpdate", "CommentInDB",
    "CommentAndDiscussionCreate", "Evaluation", "EvaluationCreate", "EvaluationUpdate",
    "EvaluationInDB",
    "User", "UserCreate", "UserUpdate", "UserUpdatePassword", "UserInDB", "Token", "TokenData",
    "DocumentPermission", "DocumentPermissionCreate", "DocumentPermissionUpdate",
    "DocumentPermissionInDB",
]
