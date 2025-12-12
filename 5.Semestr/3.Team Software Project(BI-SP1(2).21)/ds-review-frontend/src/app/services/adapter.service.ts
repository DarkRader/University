import { Injectable } from '@angular/core'
import { PreviewData } from '../objects/preview-data'
import { ApiPreviewData } from '../objects/api-preview-data'
import { ApiCommentData } from '../objects/api-comment-data'
import { CommentData } from '../objects/comment-data'
import { ApiCrosslinkData } from '../objects/api-crosslink-data'
import { SelectionData } from '../objects/selection-data'
import { ApiDiscussionData } from '../objects/api-discussion-data'
import { DiscussionData } from '../objects/discussion-data'
import { DiscussionState } from '../objects/discussion-state'
import { state } from '@angular/animations'
import { Evaluation } from '../objects/evaluation'
import { ApiEvaluation } from '../objects/api-evaluation'

@Injectable({
  providedIn: 'root',
})
export class AdapterService {
  IMG_SRC: string = '../../assets/img/icon_doc.png'
  IMG_DEFAULT_COLOR = '#4b45ee'

  constructor() {}

  convertToAPI(previewData: PreviewData): ApiPreviewData {
    return {
      title: previewData.text_1.toString(),
      doc_state: '',
      doc_type: 'p',
      content: previewData.text_2.toString(),
      submitted_at: new Date().toISOString(),
      closed_at: '',
      uuid: '',
      discussions: [],
    }
  }

  convertFromAPI(apiPreviewData: ApiPreviewData): PreviewData {
    return {
      img_src: this.IMG_SRC,
      text_1: apiPreviewData.title,
      text_2:
        'submitted: ' +
        this.covertToUserFriendlyDate(apiPreviewData.submitted_at),
      new_events_count: 0,
      show_icon: false,
      background_color: this.IMG_DEFAULT_COLOR,
      text_color: '#ffffff',
      uuid: apiPreviewData.uuid,
    }
  }

  convertDiscussionFromAPI(apiDiscussion: ApiDiscussionData): DiscussionData {
    const apiComments: ApiCommentData[] = apiDiscussion.comments
    const oldestComment = this.getOldestComment(apiComments)
    const convertedComments: CommentData[] = []
    for (let i = 0; i < apiComments.length; i++) {
      if (apiComments[i].uuid == oldestComment.uuid) continue
      const convertedComment = this.convertCommentFromAPI(apiComments[i])
      convertedComments.push(convertedComment)
    }
    return {
      selectionData: this.convertCrosslinkToSelectionData(
        apiDiscussion.crosslink
      ),
      uuid: apiDiscussion.uuid,
      content: oldestComment.content,
      comments: convertedComments,
      document_uuid: apiDiscussion.document_uuid,
      discussionState:
        apiDiscussion.state === 'open'
          ? DiscussionState.OPEN
          : DiscussionState.RESOLVED,
    }
  }

  convertCommentToApiComment(
    comment: CommentData,
    discussionUUID: string
  ): ApiCommentData {
    return {
      content: comment.text_content.toString(),
      uuid: '',
      created_at: '',
      discussion_uuid: discussionUUID,
    }
  }

  convertDiscussionToAPI(discussion: DiscussionData): ApiDiscussionData {
    return {
      crosslink: this.convertSelectionToCrosslink(discussion.selectionData),
      uuid: discussion.uuid,
      comments: [],
      document_uuid: discussion.document_uuid,
      state:
        discussion.discussionState === DiscussionState.OPEN ? 'open' : 'closed',
    }
  }

  convertSelectionToCrosslink(selection: SelectionData) {
    return {
      start_index: selection.initialIndex,
      end_index: selection.stopIndex,
      element_ids: selection.elementsIds,
    }
  }

  convertCrosslinkToSelectionData(crosslink: ApiCrosslinkData): SelectionData {
    return {
      id: 0,
      initialIndex: crosslink.start_index,
      stopIndex: crosslink.end_index,
      elementsIds: crosslink.element_ids,
    }
  }

  convertCommentFromAPI(apiCommentData: ApiCommentData): CommentData {
    return {
      username: 'anonym',
      date: '',
      text_content: apiCommentData.content,
      text_username_color: '#000000',
      text_color_open: '#000000',
      text_color_closed: '#000000',
      img_closed_src: '',
      img_open_src: '../../assets/img/icon_tick.png',
      background_color: '#fcfcfc',
      is_submitter: false,
      is_open: true,
      comment_id: '0',
      selections: [],
      delimiters: [],
    }
  }

  covertToUserFriendlyDate(dateStr: string) {
    const date = new Date(dateStr)
    const formattedDate = date.toLocaleDateString('en-GB')
    return formattedDate
  }

  getOldestComment(comments: ApiCommentData[]): ApiCommentData {
    let oldest = comments[0]
    let oldestDate = new Date(comments[0].created_at)
    let i = 1
    while (i < comments.length) {
      let currDate = new Date(comments[i].created_at)
      if (currDate < oldestDate) {
        oldest = comments[i]
        oldestDate = currDate
      }
      i++
    }
    return oldest
  }

  convertStateToApiString(state: DiscussionState) {
    if (state === DiscussionState.OPEN) {
      return 'open'
    } else {
      return 'resolved'
    }
  }

  convertToEvaluaation(apiEval: ApiEvaluation){
    const evaluation:Evaluation =
    {
      rating:apiEval.rating,
      state:apiEval.state
    }
    return eval;
  }
  convertToAPIEvaluaation(evaluation: Evaluation, documentUUID: string){
    const apiEval:ApiEvaluation =
    {
      rating:evaluation.rating,
      state:evaluation.state,
      document_uuid:documentUUID
    }
    return apiEval;
  }
}
