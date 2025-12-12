import { TestBed } from '@angular/core/testing';
import { ApiService } from 'src/app/services/api.service';
import {DiscussionCommentService} from 'src/app/services/discussion-comment.service'
import { DiscussionState } from '../objects/discussion-state';
import { DiscussionData } from 'src/app/objects/discussion-data'; 


const mockDiscussionData:DiscussionData ={
    selectionData: {
        id: 1,
        initialIndex: 2,
        stopIndex: 3,
        elementsIds: []
    },
    content: 'HELLO WORLD',
    comments: [],
    uuid: 'uuid1234',
    document_uuid: 'docuuid1234',
    discussionState: DiscussionState.OPEN
}

describe('DiscussionCommentService', () => {
  let discussionCommentService: DiscussionCommentService;
  let apiServiceSpy: jasmine.SpyObj<ApiService>; // You may need to create a spy for ApiService

  beforeEach(() => {
    const spy = jasmine.createSpyObj('ApiService', ['postComment', 'putDiscussionForDocument']);

    TestBed.configureTestingModule({
      providers: [
        DiscussionCommentService,
        { provide: ApiService, useValue: spy }
      ]
    });

    discussionCommentService = TestBed.inject(DiscussionCommentService);
    apiServiceSpy = TestBed.inject(ApiService) as jasmine.SpyObj<ApiService>;
  });

  it('should post a comment to discussion', () => {
    const content = 'Test comment content';
    const discussionUUID = '123456789';

    // Call the method
    discussionCommentService.postCommentToDiscussion(content, discussionUUID);

    // Expect that the ApiService's postComment method was called with the correct parameters
    expect(apiServiceSpy.postComment).toHaveBeenCalledWith({
      comment: {
        content: content,
        discussion_uuid: discussionUUID,
      },
    });
  });

  it('should update discussion state', () => {
    // Call the method
    discussionCommentService.updateDiscussionState(mockDiscussionData);

    // Expect that the ApiService's putDiscussionForDocument method was called with the correct parameters
    const expectedCrosslink = {start_index:2,end_index:3,element_ids:[]};
    const expectedState = 'open';

    expect(apiServiceSpy.putDiscussionForDocument).toHaveBeenCalledWith(
      {
        crosslink: expectedCrosslink,
        state: expectedState,
      },
      mockDiscussionData.uuid
    );
  });
});
