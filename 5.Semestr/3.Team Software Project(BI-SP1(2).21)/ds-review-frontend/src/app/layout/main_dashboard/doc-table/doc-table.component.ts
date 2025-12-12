import { Component } from '@angular/core';
import { BehaviorSubject } from 'rxjs/internal/BehaviorSubject';
import { PreviewData } from 'src/app/objects/preview-data';
import { DocViewService } from '../../../services/doc-view.service';

@Component({
  selector: 'app-doc-table',
  templateUrl: './doc-table.component.html',
  styleUrls: ['./doc-table.component.scss']
})
export class DocTableComponent {

  previewData: BehaviorSubject<PreviewData[]> = new BehaviorSubject<PreviewData[]>([])
  previewDataArray: PreviewData[] = []

  constructor(
    private docViewService:DocViewService
  ) {}

  ngOnInit(): void {
    this.docViewService.getData()
    this.docViewService.getPreviewData().subscribe((data) => {
      this.previewDataArray = data
    })
  }

  goToDocumentReviever( row : PreviewData) {
    this.docViewService.goToDocumentReviever(row.uuid);
  }

  columns = [
    {
      columnDef: 'title',
      header: 'Title',
      cell: ( data : PreviewData) => `${data.text_1}`,
    },
    {
      columnDef: 'submitted',
      header: 'Submitted',
      cell: ( data : PreviewData) => `${data.text_2}`,
    },
  ];
  displayedColumns = this.columns.map(c => c.columnDef);


}
