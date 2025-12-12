import { Injectable } from '@angular/core'
import { BehaviorSubject, map } from 'rxjs'
import { ApiService } from 'src/app/services/api.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { AdapterService } from 'src/app/services/adapter.service'
@Injectable({
  providedIn: 'root',
})
export class DiscussionWindowService {
  private discussionsBehavioural: BehaviorSubject<DiscussionData[]> =
    new BehaviorSubject<DiscussionData[]>([])

  constructor(
    private apiService: ApiService,
    private adapter: AdapterService
  ) {}

  getDiscussionBehavioural() {
    return this.discussionsBehavioural
  }

  scrollToTop(){
    var scrollableContent = document.getElementById("discussion-window");
    if (scrollableContent) {
      scrollableContent.scrollTop = 0;
    }
  }

  async getDiscussionsData(docUUID: string): Promise<void> {
    try {
      const apiData = await this.apiService.getDiscussionsForDocument(docUUID).toPromise();
  
      const discussions = apiData!.map(apiItem => this.adapter.convertDiscussionFromAPI(apiItem));
  
      this.discussionsBehavioural.next(discussions);
    } catch (error) {
      // Handle any errors that occurred during the operation
      console.error("Error getting discussions data:", error);
    }
  }
  
}
