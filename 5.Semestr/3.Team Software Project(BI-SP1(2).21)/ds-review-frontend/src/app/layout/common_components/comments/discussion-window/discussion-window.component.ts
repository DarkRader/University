import { Component, OnInit } from '@angular/core'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { DiscussionWindowService } from '../../../../services/discussion-window.service'
import { ActivatedRoute } from '@angular/router'

@Component({
  selector: 'app-discussion-window',
  templateUrl: './discussion-window.component.html',
  styleUrls: ['./discussion-window.component.scss'],
})
export class DiscussionWindowComponent implements OnInit {
  discussionsDataArray: DiscussionData[] = []

  constructor(
    private discussionWindowService: DiscussionWindowService,
    private route: ActivatedRoute
  ) {
  }

  ngOnInit(): void {
    this.route.params.subscribe((params) => {
      let document_uuid = params['public_document_uuid']
      this.discussionWindowService.getDiscussionsData(document_uuid)
    })

    this.discussionWindowService
      .getDiscussionBehavioural()
      .subscribe((data) => {
        this.discussionsDataArray = data
      })
  }
}
