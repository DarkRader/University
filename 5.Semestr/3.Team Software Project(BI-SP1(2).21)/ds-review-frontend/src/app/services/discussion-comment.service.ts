import { Injectable } from '@angular/core'
import { ApiService } from 'src/app/services/api.service'
import { AdapterService } from 'src/app/services/adapter.service'
import { DiscussionData } from 'src/app/objects/discussion-data'

@Injectable({
  providedIn: 'root',
})
export class DiscussionCommentService {
  constructor(private api: ApiService, private adapter: AdapterService) {}

  async postCommentToDiscussion(
    _content: string,
    _discussionUUID: string
  ) {
    return this.api.postComment({
      comment: {
        content: _content,
        discussion_uuid: _discussionUUID,
      },
    })
  }

  updateDiscussionState(discussionData: DiscussionData) {
    const _crosslink = this.adapter.convertSelectionToCrosslink(
      discussionData.selectionData
    )
    const _state = this.adapter.convertStateToApiString(
      discussionData.discussionState
    )
    this.api.putDiscussionForDocument(
      {
        crosslink: _crosslink,
        state: _state,
      },
      discussionData.uuid
    )
  }
}
