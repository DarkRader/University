import { Component } from '@angular/core';
import { DocumentService } from '../../services/document.service';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-doc-submission',
  templateUrl: './doc-submission.component.html',
  styleUrls: ['./doc-submission.component.scss']
})
export class DocSubmissionComponent {
  documentForm: FormGroup;

  constructor(private fb: FormBuilder, private docService: DocumentService) {
    this.documentForm = this.fb.group({
      documentText: ['', Validators.required],
      dsrToken: ['',Validators.required] // You can set the default value here if needed
    });
  }

  // onSubmit method
  async onSubmit() {
    if (this.documentForm.valid) {
      const documentText = this.documentForm.get('documentText')!.value;
      const dsrToken = this.documentForm.get('dsrToken')!.value;

      try {
        const success = await this.docService.submitDocument(documentText, dsrToken);

        if (success) {
          alert("SUCCESSFULLY SUBMITTED");
          this.documentForm.reset();
        } else {
          alert("SUBMISSION FAILED");
        }
      } catch (error) {
        console.error('An error occurred:', error);
      }
    } else {
      alert("INVALID SUBMISSION");
    }
  }
}
