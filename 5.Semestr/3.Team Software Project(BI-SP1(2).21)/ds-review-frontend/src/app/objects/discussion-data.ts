import { CommentData } from './comment-data'
import { SelectionData } from './selection-data'
import { DiscussionState } from './discussion-state'

export interface DiscussionData {
  selectionData: SelectionData
  content: string
  comments: CommentData[]
  uuid: string
  document_uuid: string
  discussionState: DiscussionState
}
