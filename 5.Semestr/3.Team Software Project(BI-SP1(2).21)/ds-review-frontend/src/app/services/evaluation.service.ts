import { Injectable } from '@angular/core';
import { Evaluation } from '../objects/evaluation';
import { ApiService } from './api.service';
import { ApiEvaluation } from '../objects/api-evaluation';
import { AdapterService } from './adapter.service';
import { Subject, lastValueFrom } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class EvaluationService {

  private evaluationDataSubject = new Subject<ApiEvaluation[]>();
  evalData$ = this.evaluationDataSubject.asObservable();

  constructor(private api: ApiService, private adapter: AdapterService) { }

  async postEvaluation(evaluation: Evaluation, documentUUID: string): Promise<any> {
    const apiEval: ApiEvaluation = this.adapter.convertToAPIEvaluaation(evaluation, documentUUID);
    const observable = this.api.postEvaluation(apiEval);
    return lastValueFrom(observable);
  }

  getEvaluationsForDocument(documentUUID: string) {
      this.api.getEvaluationsForDocument(documentUUID).subscribe({
      next : (evaluations: ApiEvaluation[]) => {
        console.log('Evaluations:', evaluations);
        this.evaluationDataSubject.next(evaluations)
      },
      error: (err) => console.log("ERR")
    })
  }
}
