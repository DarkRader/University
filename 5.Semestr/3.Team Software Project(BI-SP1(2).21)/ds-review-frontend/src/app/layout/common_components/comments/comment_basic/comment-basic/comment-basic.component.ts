import { Component, Input } from '@angular/core'
import { CommentData } from 'src/app/objects/comment-data'

@Component({
  selector: 'app-comment-basic',
  templateUrl: './comment-basic.component.html',
  styleUrls: ['./comment-basic.component.scss'],
})
export class CommentBasicComponent {
  @Input() commentData: CommentData | undefined
}
