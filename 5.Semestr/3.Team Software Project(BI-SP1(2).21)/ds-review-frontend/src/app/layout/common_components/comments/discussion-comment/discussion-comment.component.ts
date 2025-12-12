import {
  ChangeDetectorRef,
  Component,
  Input,
  OnInit,
} from '@angular/core'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { DiscussionCommentService } from '../../../../services/discussion-comment.service'
import { DiscussionWindowService } from '../../../../services/discussion-window.service'
import { DiscussionState } from 'src/app/objects/discussion-state'
import { DocumentService } from '../../../../services/document.service'
import { DiscussionPosterComponent } from '../../discussion_poster/discussion-poster/discussion-poster.component'

@Component({
  selector: 'app-discussion-comment',
  templateUrl: './discussion-comment.component.html',
  styleUrls: ['./discussion-comment.component.scss'],
})
export class DiscussionCommentComponent implements OnInit {
  answersShown = false
  answerInputShown = false
  focusCircleSelected = false;
  btnSeeCommentsText = 'See Comments'
  btnChangeDiscussionState = ''
  numOfComments = 0
  scrollToDefined = false
  @Input() discussionData: DiscussionData | undefined
  textInput = ''
  showResolved = false

  constructor(
    private discussionCommentService: DiscussionCommentService,
    private discussionWindowService: DiscussionWindowService,
    private docService: DocumentService,
    private cdr: ChangeDetectorRef
  ) {}

  ngOnInit(): void {
    this.focusCircleSelected = this.discussionData?.selectionData.initialIndex == DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED? false : true;
    this.numOfComments = this.discussionData?.comments.length! | 0
    this.btnSeeCommentsText = 'See Comments (' + this.numOfComments + ')'
    this.setDiscussionState()
    if (this.discussionData?.discussionState === DiscussionState.OPEN) {
      this.showResolved = false
    } else if (
      this.discussionData?.discussionState === DiscussionState.RESOLVED
    ) {
      this.showResolved = true
    }
  }

  showAnswerInput() {
    this.answerInputShown = !this.answerInputShown
  }

  showAnswers() {
    this.answersShown = !this.answersShown
  }

  scrollToPoint(){
    // If comment has no focus circle
    if(this.discussionData?.selectionData.initialIndex == DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED){
      return;
    }
    // Scrolling document
    this.docService.scrollTo(this.discussionData?.selectionData.initialIndex!,this.discussionData?.selectionData.stopIndex!)
    this.docService.showFocusCircle(this.discussionData?.selectionData.initialIndex!,this.discussionData?.selectionData.stopIndex!,false,"blue")
  }

  async postCommentToDiscussion() {
    try {

      await this.discussionCommentService.postCommentToDiscussion(
        this.textInput,
        this.discussionData?.uuid!
      );
  
      // The comment has been successfully posted
      // Now, update discussions
      const discussionsData = await this.discussionWindowService.getDiscussionsData(
        this.discussionData?.document_uuid!
      )
  
    } catch (error) {
      console.error('Error:', error);
    }
  }

  changeDiscussionState() {
    console.log('change 1:' + this.showResolved)
    console.log(this.showResolved)
    if (this.discussionData?.discussionState === DiscussionState.OPEN) {
      this.discussionData!.discussionState = DiscussionState.RESOLVED
      this.showResolved = true
    } else if (
      this.discussionData?.discussionState === DiscussionState.RESOLVED
    ) {
      this.discussionData!.discussionState = DiscussionState.OPEN
      this.showResolved = false
    }
    console.log('change 2:' + this.showResolved)
    this.cdr.detectChanges()
    this.setDiscussionState()

    this.discussionCommentService.updateDiscussionState(this.discussionData!)
    this.cdr.detectChanges()
  }

  private setDiscussionState() {
    const txt =
      this.discussionData!.discussionState === DiscussionState.OPEN
        ? 'resolved'
        : 'open'
    this.btnChangeDiscussionState = 'Mark discussion as ' + txt
    this.cdr.detectChanges()
  }
}
