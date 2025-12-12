# Requirements Analysis

## 1. Participants

Within the scope of SP1, only a single type of user was implemented. Different permission levels for working with documents will be implemented in SP2. However, distinguishing the participants still makes sense for the purposes of describing use cases.

### 1.1 Submitter

The submitter uploads to the application a file created using the DSW in order to receive feedback from reviewers. They can upload additional documents and manage the documents they have submitted (change state, delete). The submitter can also communicate with reviewers by responding to comments on the document.

### 1.2 Reviewer

A reviewer adds evaluations and comments to documents assigned to them by the submitter. Reviewers can interact with their own comments. Reviewers for each document will be assigned by an external authority responsible for managing the DSR.

## 2. Use Cases

### 2.1 Document Manipulation

This chapter describes how users can create new documents, view them, and interact with them.

#### **UC1 – Create Document**

Allows users to send a document from the DSW to our application so it can be reviewed and receive feedback from other users.

Documents cannot be edited within our application, nor can they be updated through the DSW. Every modification will be represented as uploading a new version of the document.

**Main Scenario:**

1. The submitter clicks Add Document in our application and is redirected to the Data Stewardship Wizard.
2. The submitter selects a document in the DSW.
3. The document is sent to our application in one of the supported formats.
4. The system creates the document in the application.
5. The document becomes visible in the dashboard and document list for the submitter and the assigned reviewers, who will gain access to its review.

**Alternative Scenario:**

1. The submitter opens the Data Stewardship Wizard in their browser.
2. Continues from step 2 of the main scenario.

#### **UC2 – Close Document**

The submitter may close a document (making it no longer possible for anyone to interact with it).
This can be done either from the list of documents or from the document detail page.
Reviewers cannot close documents.
A closed document cannot be deleted or removed from the list.

#### **UC3 – Reopen Document**

If a submitter has previously closed a document, they can reopen it.

This can be done either from the document list or from the document detail page.

Reviewers do not have this permission.

#### **UC4 – View Document List**

A user can view a list of documents they have access to. They can filter the list based on whether they are the submitter or a reviewer of a document.

The user can hide already closed documents.

The documents cannot be arbitrarily sorted; they are sorted by state and creation date.

#### **UC5 – View Document**

A user can view an individual document. The page will display both the document itself and its associated comments.
The submitter will also see the reviewers’ evaluations of the document.
All comments are displayed by default, but the user can hide comments marked as resolved.

### 2.2 Comments and Ratings

This chapter describes how submitters and reviewers interact with documents, specifically how comments and ratings work.
Ratings were not implemented in SP1.
Comments may reply to one another, forming a discussion thread. Comments can be edited, deleted, and marked as resolved.

#### **UC6 – Add Comment and Conduct Discussion**

Submitters and reviewers can add comments to a specific part of the document and reply to existing comments.

**Main Scenario:**

1. The use case begins when a user wants to comment on the document.
2. Include (View Document)
3. The user adds a comment to a specific part of the document.
4. Users may engage in a discussion under this comment by adding further replies.
5. Continues from step 3 of this scenario.

**Exceptions:**

1. The user does not have to add any comment or participate in the discussion at all.

**Alternative Scenario (Replying to an Existing Comment):**

The scenario begins at step 3 of the main scenario if the user chooses to reply under an existing comment.

1. The user adds a comment within an existing discussion thread.

#### **UC7 – Mark Comment as “Resolved”**

The submitter can mark a comment as resolved, which prevents further discussion under it.
The submitter can revert the comment back to open (the default state), enabling further discussion.

**Main Scenario:**

1. Include (View Document)
2. The submitter marks a comment as _resolved_.
3. No additional comments can be added under it. Comments marked as _resolved_ remain visible, including their discussion history.
4. The submitter may revert the comment back to _open_.
5. Continues from step 2 of this scenario or ends.

#### **UC8 – Add Document Rating**

**Not implemented in SP1!**

A reviewer may rate a document after reading it. The rating will be represented as selecting 1–5 stars.
The reviewer may change their rating.
Each rating may include a discussion thread similar to comment threads on document content. 

## 3. General Requirements

- N1 – Web Availability
  - The system will be available as a web application viewable in a browser; no special mobile device application is required. The application will be responsive to support viewing on tablets and mobile devices.
  - Priority: M
  - Category: U
- N2 – Responsive Design
  - The application will be responsive to support easy viewing on tablets and mobile devices.
  - Priority: S
  - Category: U
- N3 – Integration with the DSW Portal
  - The application will be open to further modifications, extensions, and integration with the DSW portal.
  - Priority: W
  - Category: S
- N4 – Reactive Display of Current Comments
  - When a document is opened, the application will always show the most up-to-date comments without requiring a page reload.
  - Priority: C
  - Category: U
- N5 – Application Performance
  - The application will respond in under 1 second when displaying current comments.
  Opening or closing documents will take no longer than 5 seconds.
  - Priority: S
  - Category: P
- N6 – User Interface
  - The application will be operable through a user interface. It will support standard features expected of a typical web application UI, specifically:
    - Switching between dark and light mode.
    - Sorting and filtering documents on the dashboard (the dashboard is the home page shown after logging in; it aggregates all documents related to the user as submitter or reviewer and provides navigation to other app functionalities).
    - Confirmation dialogs for irreversible actions (e.g., deleting a document) to prevent accidental deletion.
    - Ability to add a document rating either by entering a specific number or using a mouse (interactive progress bar).
  - Priority: S
  - Category: U
- N7 – Localization
  - The application will be available in multiple supported languages and can be easily extended with additional languages.
  - Priority: C
  - Category: U

## 4. Negative Scope – What the System Will Not Do

- NV1 – No Document Creation
  - The application will only accept documents generated by the DS Wizard.
- NV2 – No Document Modification
- NV3 – Limited Document Format Support
  - Initially, the application will only accept HTML documents; support for additional formats is optional.
- NV4 – No Automatic Document Analysis
  - The application will not automatically assess or evaluate document content.
- NV5 – Web Application Only
  - The application will be available only as a web-based system; no mobile or desktop clients will exist.
