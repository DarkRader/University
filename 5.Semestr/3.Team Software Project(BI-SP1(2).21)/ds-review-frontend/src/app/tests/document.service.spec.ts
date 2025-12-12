import { TestBed, fakeAsync, flush, tick } from '@angular/core/testing';
import { DocumentService } from 'src/app/services/document.service';
import { ApiService } from 'src/app/services/api.service';
import { of, throwError } from 'rxjs';
import { ApiEndpointsService } from '../services/api-endpoints.service';

describe('DocumentService', () => {
  let service: DocumentService;
  let apiServiceSpy: jasmine.SpyObj<ApiService>;

  beforeEach(() => {
    apiServiceSpy = jasmine.createSpyObj('ApiService', ['getSelectedDocument', 'submitDocument']);

    TestBed.configureTestingModule({
      providers: [
        DocumentService,
        { provide: ApiService, useValue: apiServiceSpy },
      ],
    });

    service = TestBed.inject(DocumentService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
  
  it('should submit document successfully', fakeAsync(() => {
    // Arrange
    const plainContent = 'Document content';
    const dsrToken = 'dsrToken';
    apiServiceSpy.submitDocument.and.returnValue(of({ code: 200 }));

    // Act
    let result: Boolean | undefined;
    service.submitDocument(plainContent, dsrToken).then(res => result = res);
    tick();

    // Assert
    expect(result).toBe(true);
    expect(apiServiceSpy.submitDocument).toHaveBeenCalledWith(plainContent, dsrToken);
  }));

  it('should handle HTTP error when submitting document', fakeAsync(() => {
    // Arrange
    const plainContent = 'Document content';
    const dsrToken = 'dsrToken';
    const expectedError = { status: 422, statusText: 'Validation Error' };
    apiServiceSpy.submitDocument.and.returnValue(throwError(()=>expectedError));

    // Act
    let result: Boolean | undefined;
    service.submitDocument(plainContent, dsrToken).then(res => result = res);
    tick();

    //Assert
    expect(result).toBe(false); 
    expect(apiServiceSpy.submitDocument).toHaveBeenCalledWith(plainContent, dsrToken);
  }));
  
});
