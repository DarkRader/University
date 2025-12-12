import { TestBed } from '@angular/core/testing';
import { AdapterService } from 'src/app/services/adapter.service';
import { CommentData } from '../objects/comment-data';
import { DiscussionState } from '../objects/discussion-state';;
import { ApiDiscussionData } from '../objects/api-discussion-data';
import { DiscussionData } from '../objects/discussion-data';
import { ApiPreviewData } from '../objects/api-preview-data';
import { PreviewData } from '../objects/preview-data';

describe('AdapterService', () => {
  let adapterService: AdapterService;

  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [AdapterService],
    });
    adapterService = TestBed.inject(AdapterService);
  });

  it('should convert PreviewData to ApiPreviewData', () => {
    const previewData: PreviewData = {
      img_src: 'image.png',
      text_1: 'Title',
      text_2: 'Content',
      new_events_count: 0,
      show_icon: false,
      background_color: '#FFFFFF',
      text_color: '#000000',
      uuid: '123',
    };

    const apiPreviewData = adapterService.convertToAPI(previewData);

    expect(apiPreviewData.title).toBe('Title');
    expect(apiPreviewData.doc_state).toBe('');
    expect(apiPreviewData.doc_type).toBe('p');
    expect(apiPreviewData.content).toBe('Content');
  });

  it('should convert ApiPreviewData to PreviewData', () => {
    const apiPreviewData: ApiPreviewData = {
      title: 'Title',
      doc_state: '',
      doc_type: 'p',
      content: 'Content',
      submitted_at: new Date().toISOString(),
      closed_at: '',
      uuid: '123',
      discussions: [],
    };

    const previewData = adapterService.convertFromAPI(apiPreviewData);

    expect(previewData.img_src).toBe(adapterService.IMG_SRC);
    expect(previewData.text_1).toBe('Title');
    expect(previewData.text_2).toContain('submitted:');
    expect(previewData.uuid).toBe('123')
  });

  it('should convert DiscussionData from API', () => {
    const apiDiscussionData: ApiDiscussionData = {
      crosslink: { start_index: 1, end_index: 10, element_ids: ['1', '2'] },
      uuid: 'discussionUUID',
      comments: [
        {
            content:'OLDEST_COMMENT',
            uuid:'1234',
            created_at: '2020-12-18T14:11:09.160Z',
            discussion_uuid:'12345'
        },
        {
            content:'RESPONSE_COMMENT',
            uuid:'r1234',
            created_at: '2022-12-18T14:11:09.160Z',
            discussion_uuid:'r12345'
        },

      ],
      document_uuid: 'documentUUID',
      state: 'open',
    };

    const discussionData = adapterService.convertDiscussionFromAPI(apiDiscussionData);

    expect(discussionData.uuid).toBe('discussionUUID');
    expect(discussionData.content).toBe('OLDEST_COMMENT');
    expect(discussionData.comments.length).toBe(1)
  });

  it('should convert CommentData to ApiCommentData', () => {
    const commentData: CommentData = {
      username: 'user1',
      date: '2023-01-01',
      text_content: 'Comment text',
      text_username_color: '#000000',
      text_color_open: '#000000',
      text_color_closed: '#000000',
      img_closed_src: '',
      img_open_src: 'image.png',
      background_color: '#fcfcfc',
      is_submitter: false,
      is_open: true,
      comment_id: '1',
      selections: [],
      delimiters: [],
    };

    const apiCommentData = adapterService.convertCommentToApiComment(commentData, 'discussionUUID');

    expect(apiCommentData.content).toBe('Comment text');
    expect(apiCommentData.uuid).toBe('');
  });

  it('should convert DiscussionData to API', () => {
    const discussionData: DiscussionData = {
      selectionData: { id: 1, initialIndex: 1, stopIndex: 10, elementsIds: ['1', '2'] },
      uuid: 'discussionUUID',
      content: 'Discussion text',
      comments: [],
      document_uuid: 'documentUUID',
      discussionState: DiscussionState.OPEN,
    };

    const apiDiscussionData = adapterService.convertDiscussionToAPI(discussionData);

    expect(apiDiscussionData.uuid).toBe('discussionUUID');
    expect(apiDiscussionData.comments).toEqual([]);
    expect(apiDiscussionData.state).toBe('open')
  });
});
