import { Injectable } from '@angular/core'
import { BehaviorSubject, Observable, Subject, catchError, lastValueFrom, map, of } from 'rxjs'
import { ApiService } from './api.service';
import { DiscussionPosterComponent } from '../layout/common_components/discussion_poster/discussion-poster/discussion-poster.component';

@Injectable({
  providedIn: 'root',
})
export class DocumentService {
  private documentContentSubject = new Subject<string>()
  public focusCirclePosition = new BehaviorSubject<[number, number]>([DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED,DiscussionPosterComponent.FOCUS_CIRCLE_UNDEFINED]);
  focusCircle: HTMLElement | undefined;
  

  constructor(private apiService: ApiService) {}

  /**
   *
   * @param isSubmitter is document opened in app by submitter?, true = submitter
   * @param documentPublicUUID
   */
  fetchDocumentContent(isSubmitter: boolean, documentPublicUUID: string): void {
    this.apiService
      .getSelectedDocument(isSubmitter, documentPublicUUID.toString())
      .subscribe((data) => {
        this.documentContentSubject.next(data.content)
      })
  }

  /**
   * @returns Document content as observable (as of now plain text).
   */
  getDocumentContent(): Observable<string> {
    return this.documentContentSubject.asObservable()
  }

  updateFocusCirclePosition(x:number, y:number){
    this.focusCirclePosition.next([x,y]);
  }

  scrollTo(x:number, y:number){
    scrollTo(x,y - window.innerHeight / 2);
  }

  showFocusCircle(offsetX: number, offsetY: number, timeout: boolean, color:string){
    this.focusCircle!.style.left = `${offsetX}px`;
    this.focusCircle!.style.top = `${offsetY}px`;
    this.focusCircle!.classList.remove("hidden");
    this.focusCircle!.style.backgroundColor = color;
    // Add a setTimeout to hide the circle after 2 seconds
    if(timeout){
      setTimeout(() => {
        this.focusCircle!.classList.add("hidden");
      }, 2000); // 2000 milliseconds = 2 seconds
    }
  }


  async submitDocument(plainContent: string, dsrToken: string): Promise<Boolean> {
    return await lastValueFrom(
      this.apiService.submitDocument(plainContent, dsrToken)
        .pipe(
          map(() => true),
          catchError(() => of(false))
        )
    );
  }


}
