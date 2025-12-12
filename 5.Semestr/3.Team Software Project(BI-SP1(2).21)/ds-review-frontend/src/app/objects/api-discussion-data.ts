import { ApiCommentData } from './api-comment-data'
import { ApiCrosslinkData } from './api-crosslink-data'
import { DiscussionState } from './discussion-state'

export interface ApiDiscussionData {
  crosslink: ApiCrosslinkData
  uuid: string
  comments: ApiCommentData[]
  document_uuid: string
  state: string
}
