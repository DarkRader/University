import { Component, OnInit, ViewChild } from '@angular/core'
import { DiscussionPosterService } from '../../../../services/discussion-poster.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { ActivatedRoute } from '@angular/router'
import { DiscussionWindowService } from '../../../../services/discussion-window.service'
import { DiscussionState } from 'src/app/objects/discussion-state'
import { DocumentService } from '../../../../services/document.service'

@Component({
  selector: 'app-discussion-poster',
  templateUrl: './discussion-poster.component.html',
  styleUrls: ['./discussion-poster.component.scss'],
})
export class DiscussionPosterComponent implements OnInit {
  static FOCUS_CIRCLE_UNDEFINED = -1
  btnPostDiscussionTxt = 'Post discussion'
  textNotSelected = 'PLEASE SELECT TEXT'
  textSelected = 'TEXT SELECTED'
  documentUUID: string = ''
  focusCircleCoordinates: [number, number] = [DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED,DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED]
  textInput = ''

  constructor(
    private posterService: DiscussionPosterService,
    private route: ActivatedRoute,
    private discussionWindowService: DiscussionWindowService,
    private docService: DocumentService
  ) {}

  ngOnInit(): void {
    this.subscribeToRouteParams()
    this.docService.focusCirclePosition.subscribe( position => {
      this.focusCircleCoordinates = position;
      console.log(this.focusCircleCoordinates)
    })
  }
  /**
   * Calls services which will post new comment (as new discussion).
   * @returns
   */
  postDiscussion() {
    console.log(this.focusCircleCoordinates + ' ' + DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED)
    const discussionData = this.getDiscussionData()
    this.postAndThenUpdate(discussionData)
  }

  async postAndThenUpdate(discussionData: DiscussionData) {
    try {
      await this.posterService.postDiscussion(discussionData);
      await this.discussionWindowService.getDiscussionsData(this.documentUUID);
      this.clearInput();
    } catch (error) {
      console.error("Error updating discussions:", error);
    }
  }

  private subscribeToRouteParams() {
    this.route.params.subscribe((params) => {
      const uuid = params['public_document_uuid']
      this.documentUUID = uuid
    })
  }

  private getDiscussionData(): DiscussionData{
    return {
      selectionData: {
        id:0,
        initialIndex: this.focusCircleCoordinates?.[0],
        stopIndex: this.focusCircleCoordinates?.[1],
        elementsIds:[]
      },
      uuid: '',
      content: this.textInput,
      comments: [],
      document_uuid: this.documentUUID,
      discussionState: DiscussionState.OPEN, // always OPEN for posting new discussion
    }
  }

  /**
   * Clears input from input.
   */
  private clearInput() {
    this.textInput=''
  }
}
