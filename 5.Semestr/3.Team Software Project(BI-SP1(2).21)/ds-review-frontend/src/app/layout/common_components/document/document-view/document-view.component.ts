import { Component, ElementRef, Input, OnInit, ViewChild } from '@angular/core';
import { DocumentService } from '../../../../services/document.service'
import { ActivatedRoute } from '@angular/router'
import { DiscussionWindowService } from '../../../../services/discussion-window.service';

@Component({
  selector: 'app-document-view',
  templateUrl: './document-view.component.html',
  styleUrls: ['./document-view.component.scss'],
})
export class DocumentViewComponent implements OnInit {
  @ViewChild('componentRef', { static: true }) componentRef: ElementRef | undefined;
  documentContent: String | undefined
  @Input() isSubmitter = false
  public static TEXT_ID = 'selection'
  textIsSelected = false
  

  constructor(
    private docService: DocumentService,
    private route: ActivatedRoute,
    private el: ElementRef,
    private discussionWinService: DiscussionWindowService 
    ) {
      const componentElem = el.nativeElement as HTMLElement
      componentElem
      .addEventListener("click",(event) => {
        this.setupFocusCircle(event);
      })
    }

  ngOnInit(): void {
    this.docService.focusCircle = document.getElementById("focus-circle") as HTMLElement
    this.getDocumentContent()
  }

  /**
   * Fetches content of document. UUID retrieved from route params.
   */
  getDocumentContent() {
    this.route.params.subscribe((params) => {
      let document_uuid = null

      if (this.isSubmitter) {
        document_uuid = params['private_document_uuid']
      } else {
        document_uuid = params['public_document_uuid']
      }

      this.docService.fetchDocumentContent(this.isSubmitter, document_uuid!)
      this.docService
        .getDocumentContent()
        .subscribe((data) => (this.documentContent = data))
    })
  }

  setupFocusCircle(event:MouseEvent){
    const componentElement: HTMLElement = this.el.nativeElement;
    const rect = componentElement.getBoundingClientRect();
    const offsetX = event.clientX - rect.left;
    const offsetY = event.clientY - rect.top;
    this.docService.showFocusCircle(offsetX,offsetY,false,"red") // no timeout for selecting
    this.docService.updateFocusCirclePosition(offsetX,offsetY);
    this.discussionWinService.scrollToTop();
  }
}
