import { TestBed } from '@angular/core/testing';
import { EvaluationService } from 'src/app/services/evaluation.service';
import { ApiService } from 'src/app/services/api.service';
import { AdapterService } from 'src/app/services/adapter.service';
import { of } from 'rxjs';
import { Evaluation } from 'src/app/objects/evaluation';
import { ApiEvaluation } from 'src/app/objects/api-evaluation';

describe('EvaluationService', () => {
  let service: EvaluationService;
  let apiServiceSpy: jasmine.SpyObj<ApiService>;
  let adapterServiceSpy: jasmine.SpyObj<AdapterService>;

  beforeEach(() => {
    apiServiceSpy = jasmine.createSpyObj('ApiService', ['postEvaluation', 'getEvaluationsForDocument']);
    adapterServiceSpy = jasmine.createSpyObj('AdapterService', ['convertToAPIEvaluaation']);
    
    TestBed.configureTestingModule({
      providers: [
        EvaluationService,
        { provide: ApiService, useValue: apiServiceSpy },
        { provide: AdapterService, useValue: adapterServiceSpy },
      ],
    });

    service = TestBed.inject(EvaluationService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });

  it('should post an evaluation', async () => {
    // Arrange
    const evaluation: Evaluation = {
      rating: 5,
      state: 'good',
    };
    const documentUUID = '123';
    const apiEvaluation: ApiEvaluation = {
      rating: 5,
      state: 'good',
      document_uuid: documentUUID,
    };
    adapterServiceSpy.convertToAPIEvaluaation.and.returnValue(apiEvaluation);
    apiServiceSpy.postEvaluation.and.returnValue(of(apiEvaluation));

    // Act
    const result = await service.postEvaluation(evaluation, documentUUID);

    // Assert
    expect(result).toEqual(apiEvaluation);
    expect(adapterServiceSpy.convertToAPIEvaluaation).toHaveBeenCalledWith(evaluation, documentUUID);
    expect(apiServiceSpy.postEvaluation).toHaveBeenCalledWith(apiEvaluation);
  });

  it('should get evaluations for a document', () => {
    // Arrange
    const documentUUID = '123';
    const apiEvaluations: ApiEvaluation[] = [
      { rating: 5, state: 'good', document_uuid: documentUUID },
      { rating: 3, state: 'average', document_uuid: documentUUID },
    ];
    apiServiceSpy.getEvaluationsForDocument.and.returnValue(of(apiEvaluations));

    // Act
    service.getEvaluationsForDocument(documentUUID);

    // Assert
    service.evalData$.subscribe((evaluations) => {
      expect(evaluations).toEqual(apiEvaluations);
    });
    expect(apiServiceSpy.getEvaluationsForDocument).toHaveBeenCalledWith(documentUUID);
  });
});
