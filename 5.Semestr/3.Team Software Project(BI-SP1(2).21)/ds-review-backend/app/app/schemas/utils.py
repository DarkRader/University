"""Utils for schemas."""
from typing import Any

from pydantic import BaseModel


def as_dict(model: BaseModel) -> dict[str, Any]:
    """Convert pydantic schema to dictionary."""
    return model.dict(exclude_unset=True)
