import { Component, Input } from '@angular/core'
import { PreviewData } from '../../../objects/preview-data'
import {DocViewService } from "../../../services/doc-view.service"

@Component({
  selector: 'app-item-card',
  templateUrl: './item-card.component.html',
  styleUrls: ['./item-card.component.scss'],
})
export class ItemCardComponent {
  @Input() preview_data: PreviewData | undefined

  constructor(private docViewService : DocViewService) {}
  cardClick() {
    this.docViewService.goToDocumentReviever(this.preview_data?.uuid!)
  }
}
