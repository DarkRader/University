import { Component } from '@angular/core'
import { CONTENT_DISPLAY_STATE } from './CONTENT_DISPLAY_STATE'
import { DocViewService } from '../../../services/doc-view.service';

@Component({
  selector: 'app-main-dashboard',
  templateUrl: './main-dashboard.component.html',
  styleUrls: ['./main-dashboard.component.scss'],
})
export class MainDashboardComponent {

  contentDisplayStateEnum = CONTENT_DISPLAY_STATE;

  constructor(public docViewService: DocViewService){}
  
}
