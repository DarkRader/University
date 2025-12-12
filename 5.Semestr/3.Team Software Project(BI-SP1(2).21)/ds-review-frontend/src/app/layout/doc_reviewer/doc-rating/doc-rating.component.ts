import { Component, OnInit } from '@angular/core';
import {MatSliderModule} from '@angular/material/slider';
import {Evaluation} from "../../../objects/evaluation";
import { ActivatedRoute, Router } from '@angular/router';
import { EvaluationService } from '../../../services/evaluation.service';

interface RatingApprovatState {
  value: string;
  viewValue: string;
}

@Component({
  selector: 'app-doc-rating',
  templateUrl: './doc-rating.component.html',
  styleUrls: ['./doc-rating.component.scss']
})
export class DocRatingComponent implements OnInit{

  APPROVED: string = "approved";
  DISAPPROVED: string = "disapproved";
  documentUUID: string = '';

  constructor(private route: ActivatedRoute, private evalService: EvaluationService, private router:Router){}

  ngOnInit(): void {
    this.subscribeToRouteParams()
  }

  evaluation: Evaluation = {
    rating: 1,       // Initial value for the rating property
    state: this.DISAPPROVED // Initial value for the state property
  };

  selectedState: string | undefined;

  ratingLabel(value: number): string {
    return `${value}`;
  }

  approvalStates: RatingApprovatState[] = [
    {value: this.APPROVED, viewValue: 'Approved'},
    {value: this.DISAPPROVED, viewValue: 'Disapproved'},
  ];

  private subscribeToRouteParams() {
    this.route.params.subscribe((params) => {
      const uuid = params['public_document_uuid']
      this.documentUUID = uuid
    })
  }

  async postEvaluation(){
    try {
      const success = await this.evalService.postEvaluation(this.evaluation,this.documentUUID)

      if (success) {
        alert("SUCCESSFULLY SUBMITTED");
        this.evaluation = {rating:1,state:this.DISAPPROVED}
      } else {
        alert("SUBMISSION FAILED");
      }
    } catch (error) {
      console.error('An error occurred:', error);
    }
  }

  goToEvaluations(){ 
    this.router.navigate(['evaluations', this.documentUUID]);
  }

}
