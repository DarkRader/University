import { SelectionData } from './selection-data'

export interface CommentData {
  username: String
  date: String
  text_content: String
  text_username_color: String
  text_color_open: String
  text_color_closed: String
  img_closed_src: String
  img_open_src: String
  background_color: String
  is_submitter: Boolean
  is_open: Boolean
  comment_id: String
  selections: SelectionData[]
  delimiters: string[]
}
