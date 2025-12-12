# UML Diagram

## 1. Domain model

![UML_diag](img/uml-diagram.jpg)

## 2. Description of UML entities

### 2.1 User

Represents user account. Can have permissions to documents as a reviewer or submitter. Can create discussions and evaluations of documents, depending on its permission to the documents. Can write comments to discussions or optionally to evaluations. As a submitter can submit a document.
| Attribute name | Description |
|----------------|-------------|
| username | User's username |
| password | User's password |
| first_name | User's first name |
| last_name | User's last name |
| email | The contact email of the user to which links for reviewing documents will be sent, and other important information |
| registered_at | The date when the user's account was created |

### 2.2 Document

The submitted document is for review. Can have some evaluations written by users with given permissions to this document. Also can have discussions about its parts, which can be linked to the document passages via crosslinks.
| Attribute name | Description |
|----------------|-------------|
| title |  |
| content | The contents of the entire document |
| submitted_at | The date when the user with submitter permission submitted the document |
| closed_at | The date when the user with submitter permission closed the document |
| state | The document can have two states submitted and closed |

### 2.3 Document permission

Certain user rights indicate the degree of his interaction with the document in our application.
| Attribute name | Description |
|----------------|-------------|
| role | The user can have the roles of submitter and reviewer |

### 2.4 Discussion

A discussion that reveals a certain problem, the purpose of which is to solve it
| Attribute name | Description |
|----------------|-------------|
| crosslink | Сrosslink that opens the discussion |
| state | The document can have two states opened and resolved |

### 2.5 Comment

Comments with which the user can conduct a discussion
| Attribute name | Description |
|----------------|-------------|
| content | The content of a comment to a specific discussion or evaluation |
| created_at | The date at which the comment was created |

### 2.6 Evaluation

Evaluation of the entire document from some “Reviewer”
| Attribute name | Description |
|----------------|-------------|
| state | Evaluation can have three states approved, disapproved and not evaluated |
| rating | Rating of the evaluation in numerical value |
| created_at | The date at which the evaluation was created |

## 3 State diagrams

### 3.1 State of the document

![General\_-\_stm_State_Diagram\_-\_document](img/state-document.jpg)

The document that is being manipulated is the main object in the application, in the process it can change its state to:

- submitted - the document is sent to our app for evaluation and receiving feedback, the user which sent this document automatically has submitter permission for the document Submitter can change back the state of the document from closed to submitted if the submitter wants to continue the review or he accidentally closed the review.
- closed - the document is closed by the submitter if he is satisfied with the review or if it is now irrelevant.

### 3.2 State of the discussion

![General\_-\_stm_State_Diagram\_-\_discussion](img/state-discussion.jpg)

Discussion can be opened by any user and its state can be changed by the submitter (user with submitter permission) to:

- opened - the discussion is open and any user can write comments in this discussion, or the submitter can reopen the discussion if he wants to continue the discussion or if he accidentally resolved/closed the discussion.
- resolved - the submitter can mark the discussion as resolved once he is satisfied with the discussion's goal or it is now irrelevant.

### 3.3 State of the evaluation

![General\_-\_Copy_of_stm_State_Diagram\_-\_evaluation](img/state-evaluation.jpg)

Only the reviewer with the permission of evaluation can create an evaluation of the document and set its state to:

- approved - if a user with reviewer permission is satisfied with the document, he approved it.
- disapproved - if a user with reviewer permission isn’t satisfied with the document, he disapproved it.
- not evaluated - user with reviewer permission may leave the evaluation state not evaluated.
