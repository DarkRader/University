import { ApiDiscussionData } from './api-discussion-data'

export interface ApiPreviewData {
  title: string
  doc_state: string
  doc_type: string
  content: string
  submitted_at: string
  closed_at: string
  uuid: string
  discussions: ApiDiscussionData[]
}
