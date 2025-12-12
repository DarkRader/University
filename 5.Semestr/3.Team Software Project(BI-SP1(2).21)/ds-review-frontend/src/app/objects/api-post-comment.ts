import { ApiCommentData } from './api-comment-data'
import { ApiDiscussionData } from './api-discussion-data'

export interface ApiPostComment {
  comment: {
    content: string
  }
  discussion: ApiDiscussionData | undefined
}
