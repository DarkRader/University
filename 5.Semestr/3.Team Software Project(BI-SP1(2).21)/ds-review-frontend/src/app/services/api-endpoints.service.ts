import { Injectable } from '@angular/core'

@Injectable({
  providedIn: 'root',
})

/**
 * This class creates URL for reaching backed endpoints.
 */
export class ApiEndpointsService {
  private readonly HOST = 'http://127.0.0.1:8000/'

  constructor() {}

  getDocumentsUrl(): string {
    return this.HOST + 'documents/'
  }

  getCommentsUrl(docUUID: string): string {
    return this.HOST + docUUID + '/comments/'
  }

  getSelectedDocumentsURL(docUUID: string): string {
    return this.HOST + 'documents/' + docUUID
  }

  getSubmittersDocumentURL(docUUID: string): string {
    return this.HOST + 'documents/submitted/' + docUUID
  }

  getDiscussionsUrlForDocument(docUUID: string): string {
    return `${this.HOST}discussions/?document_uuid=${docUUID}`
  }

  getCommentPostURL() {
    return `${this.HOST}comments/`
  }

  getPutDiscussionForDocumentURL(discussionUUID: string) {
    return this.HOST + 'discussions/' + discussionUUID
  }

  getEvaluationPostURL(){
    return this.HOST + 'evaluations/';
  }

  getRegistrationPostURL(){
    return this.HOST + 'users/register/'
  }

  getLoginPostURL(){
    return this.HOST + 'users/login/'
  }

  getUserInfoURL(){
    return this.HOST + 'users/me/'
  }

  getSubmitDocumentURL(){
    return this.HOST + 'documents/submit/'
  }

  getEvaluationsGetURL(document_uuid: string){
    return `${this.HOST}evaluations/?document_uuid=${document_uuid}`
  }

  getDefaultLoginPage(){
    return this.HOST
  }
}
