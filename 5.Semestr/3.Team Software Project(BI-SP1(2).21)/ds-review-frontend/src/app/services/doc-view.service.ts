import { Injectable } from '@angular/core';
import { BehaviorSubject, map } from 'rxjs';
import { PreviewData } from 'src/app/objects/preview-data';
import { ApiService } from './api.service';
import { AdapterService } from 'src/app/services/adapter.service';
import { CONTENT_DISPLAY_STATE } from '../layout/main_dashboard/main-dashboard/CONTENT_DISPLAY_STATE';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root'
})
export class DocViewService {

  private previewData: BehaviorSubject<PreviewData[]> = new BehaviorSubject<PreviewData[]>([]);
  private viewSubject: BehaviorSubject<CONTENT_DISPLAY_STATE> = new BehaviorSubject<CONTENT_DISPLAY_STATE>(CONTENT_DISPLAY_STATE.GRID);
  public view$ = this.viewSubject.asObservable();

  constructor(
    private apiService: ApiService,
    private adapter: AdapterService,
    private router: Router
  ) {}

  changeDocView() {
    if(this.viewSubject.getValue() === CONTENT_DISPLAY_STATE.GRID){
      this.viewSubject.next(CONTENT_DISPLAY_STATE.TABLE);
    }else{
      this.viewSubject.next(CONTENT_DISPLAY_STATE.GRID);
    }
  }

  /**
   * Calls service functions which will fetch document previewData.
   * This data is subscribed and set
   */
  getData() {
    this.apiService
      .getAllDocuments()
      .pipe(
        map((apiData) =>
          apiData.map((apiItem) => this.adapter.convertFromAPI(apiItem))
        )
      )
      .subscribe((data) => {
        this.previewData.next(data)
      })
  }

  getPreviewData() {
    return this.previewData
  }

  goToDocumentReviever(publicUUID: String) {
    this.router.navigate(['/documents', publicUUID])
  }
}
