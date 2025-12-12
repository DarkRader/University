import { Component, OnInit } from '@angular/core'
import { PreviewData } from 'src/app/objects/preview-data'
import { BehaviorSubject } from 'rxjs'
import { AdapterService } from 'src/app/services/adapter.service'
import { DocViewService } from '../../../services/doc-view.service'
@Component({
  selector: 'app-doc-grid',
  templateUrl: './doc-grid.component.html',
  styleUrls: ['./doc-grid.component.scss'],
})
export class DocGridComponent implements OnInit {
  
  previewData: BehaviorSubject<PreviewData[]> = new BehaviorSubject<PreviewData[]>([])
  previewDataArray: PreviewData[] = []

  constructor(
    private docViewService:DocViewService,
    private adapter: AdapterService
  ) {}

  ngOnInit(): void {
    this.docViewService.getData()
    this.docViewService.getPreviewData().subscribe((data) => {
      this.previewDataArray = data
    })
  }

}
