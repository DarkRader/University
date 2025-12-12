import { HttpClient, HttpHeaders } from '@angular/common/http'
import { Injectable } from '@angular/core'
import { ApiEndpointsService } from './api-endpoints.service'
import { ApiPreviewData } from '../objects/api-preview-data'
import { ApiDiscussionData } from '../objects/api-discussion-data'
import { ApiEvaluation } from '../objects/api-evaluation'
import { ApiPostRegistration } from '../objects/api-post-registration'
import { ApiUserData } from '../objects/api-user-data'
import { shareReplay } from 'rxjs'

@Injectable({
  providedIn: 'root',
})
export class ApiService {
  constructor(
    private http: HttpClient,
    private apiEndpointsServie: ApiEndpointsService
  ) {}

  getAllDocuments() {
    return this.http.get<ApiPreviewData[]>(
      this.apiEndpointsServie.getDocumentsUrl()
    )
  }

  /**
   * Fetches document content.
   * @param isSubmitter
   * @param docUUID
   * @returns
   */
  getSelectedDocument(isSubmitter: boolean, docUUID: string) {
    if (isSubmitter)
      return this.http.get<ApiPreviewData>(
        this.apiEndpointsServie.getSubmittersDocumentURL(docUUID)
      )
    else
      return this.http.get<ApiPreviewData>(
        this.apiEndpointsServie.getSelectedDocumentsURL(docUUID)
      )
  }

  getSubmitterDocument(docUUID: string) {
    return this.http.get<ApiPreviewData>(
      this.apiEndpointsServie.getSubmittersDocumentURL(docUUID)
    )
  }

  /**
   * Fetches all discussions for document (including comments)
   * @param docUUID
   * @returns
   */
  getDiscussionsForDocument(docUUID: string) {
    return this.http.get<ApiDiscussionData[]>(
      this.apiEndpointsServie.getDiscussionsUrlForDocument(docUUID)
    )
  }

  /**
   * Posts new comment, whether it is a new comment to a existing discussion, or completely new discussion,
   * needs to be set already in parameter.
   * @param apiPostComment
   */
  postComment(apiPostComment: Object) {
    console.log(this.apiEndpointsServie.getCommentPostURL())
    console.log(JSON.stringify(apiPostComment))
    return this.http
      .post(this.apiEndpointsServie.getCommentPostURL(), apiPostComment).subscribe()
  }

  putDiscussionForDocument(apiDiscussionPut: Object, discussionUUID: string) {
    console.log(JSON.stringify(apiDiscussionPut))
    this.http
      .put(
        this.apiEndpointsServie.getPutDiscussionForDocumentURL(discussionUUID),
        apiDiscussionPut
      )
      .subscribe()
  }

  postEvaluation(apiEval: ApiEvaluation){
    console.log(apiEval)
    return this.http
    .post(this.apiEndpointsServie.getEvaluationPostURL(), apiEval)
  }

  postRegistration(apiPostRegistration: ApiPostRegistration){
    return this.http.post(this.apiEndpointsServie.getRegistrationPostURL(), apiPostRegistration).pipe(shareReplay(1));
  }

  postLogin(apiPostLogin: string){
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    return this.http.post(this.apiEndpointsServie.getLoginPostURL(), apiPostLogin, {headers:headers})
  }

  getUserInfo(){
    return this.http.get<ApiUserData>(this.apiEndpointsServie.getUserInfoURL())
  }

  submitDocument(plainContent:string, dsrToken:string){
    // Create headers with the DSR token
    const headers = new HttpHeaders({
      'x-dsr-token': `${dsrToken}`,
      'Content-Type': 'text/plain'
    });
    
    // Make the HTTP request with the headers
    console.log("submitting doc http" + dsrToken)
    return this.http.post(this.apiEndpointsServie.getSubmitDocumentURL(), plainContent , { headers })
  }

  getEvaluationsForDocument(doc_uuid: string){
    return this.http.get<ApiEvaluation[]>(this.apiEndpointsServie.getEvaluationsGetURL(doc_uuid))
  }
}
