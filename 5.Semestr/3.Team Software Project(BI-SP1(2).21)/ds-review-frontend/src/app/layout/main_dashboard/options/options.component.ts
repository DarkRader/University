import { Component } from '@angular/core';
import { CONTENT_DISPLAY_STATE } from '../main-dashboard/CONTENT_DISPLAY_STATE';
import { DocViewService } from '../../../services/doc-view.service';


@Component({
  selector: 'app-options',
  templateUrl: './options.component.html',
  styleUrls: ['./options.component.scss']
})
export class OptionsComponent {

  viewState:CONTENT_DISPLAY_STATE = CONTENT_DISPLAY_STATE.GRID;
  contentDisplayStateEnum = CONTENT_DISPLAY_STATE;

  constructor(public docViewService: DocViewService){

  }

  changeDocView(){
    this.docViewService.changeDocView();
  }

}
