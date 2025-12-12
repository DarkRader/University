from datetime import datetime

import pytest

import schemas
from models import DiscussionState


@pytest.fixture(scope="module")
def crosslink_schema() -> schemas.Crosslink:
    return schemas.Crosslink(
        start_index=2,
        end_index=4,
        element_ids=["5", "6", "7"]
    )


@pytest.fixture(scope="module")
def discussion_schema(crosslink_schema) -> schemas.Discussion:
    return schemas.Discussion(
        uuid="186c30d9-94ab-4484-92d9-10836361b628",
        crosslink=crosslink_schema,
        state=DiscussionState.OPEN,
        created_at=datetime.utcnow(),
        resolved_at=None,
        document_uuid="6e3c29c6-b26b-4bee-aa27-9bf0f4273690",
        comments=[],
        evaluation_uuid=None
    )


def test_conversion_to_dict(discussion_schema):
    """Check if crosslink is correctly converted to dictionary.

    :param discussion_schema: Discussion schema.
    """
    res_dict = {field[0]: field[1] for field in discussion_schema}
    res_dict["crosslink"] = {field[0]: field[1] for field in discussion_schema.crosslink}
    assert res_dict == schemas.as_dict(discussion_schema)
