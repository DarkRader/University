import { Component, OnInit } from '@angular/core';
import { EvaluationService } from '../../services/evaluation.service';
import { ApiEvaluation } from 'src/app/objects/api-evaluation';
import { MatTableDataSource } from '@angular/material/table';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-evaluations',
  templateUrl: './evaluations.component.html',
  styleUrls: ['./evaluations.component.scss']
})
export class EvaluationsComponent implements OnInit{

  dataSource: MatTableDataSource<ApiEvaluation>;
  displayedColumns: string[] = ['state', 'rating', 'document_uuid'];

  constructor(private evaluationService: EvaluationService,private route: ActivatedRoute) {
    this.dataSource = new MatTableDataSource<ApiEvaluation>();
  }

  ngOnInit(): void {
    this.getEvaluations()
  }

  private getEvaluations(){
    this.route.params.subscribe( params => {
      const documentUuid = params['public_document_uuid'];
      this.evaluationService.getEvaluationsForDocument(documentUuid)
      this.evaluationService.evalData$.subscribe((evaluations) => {
        this.dataSource.data = evaluations;
        console.log(this.dataSource.data);
      });
    })
  }

}
