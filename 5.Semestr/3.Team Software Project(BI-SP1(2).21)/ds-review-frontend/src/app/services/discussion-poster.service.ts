import { Injectable } from '@angular/core'
import { ApiService } from 'src/app/services/api.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { AdapterService } from 'src/app/services/adapter.service'
import { ApiPostComment } from 'src/app/objects/api-post-comment'

@Injectable({
  providedIn: 'root',
})
export class DiscussionPosterService {
  constructor(
    private api: ApiService,
    private adapter: AdapterService) {}

  /**
   * Postes comment (as new discussion) -> new discussion will be posted.
   * @param discussionData
   */
  async postDiscussion(discussionData: DiscussionData) {
    const postData: ApiPostComment = {
      comment: {
        content: discussionData.content.toString(),
      },
      discussion: this.adapter.convertDiscussionToAPI(discussionData),
    }
    this.api.postComment(postData)
  }
}
