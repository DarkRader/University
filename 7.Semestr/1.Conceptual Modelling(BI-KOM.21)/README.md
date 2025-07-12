# Semestral Project

---

## Topic

Each student must prepare a semester project either individually or in pairs, meeting the specified requirements.

The topic is chosen freely by the team (student or pair). The only limitation is its suitability for application of the taught methods. The domain should be complex enough, as explained in the first lecture.

In short:  
The domain must contain a variety of different concepts, relationships between them, and rules. Otherwise, the project may be too simplistic and poorly evaluated.

Note: A real-world domain is not required — a sci-fi domain is acceptable.

**Topic registration must be done via Moodle** by the end of **Week 3**, as instructed during practical sessions.

---

## Structure and Grading

The semester project consists of two graded parts:

### 1st Part

- **Topic Analysis**
    - Suitable name for the project.
    - Description of the problem domain — including context, object properties, constraints, and process (at least one A4 page).
    - At least **3 non-trivial domain restrictions/rules**:
        - Not just cardinality or simple constraints (like non-zero values).
        - Must reflect the logic and purpose of the domain.
        - Should require complex navigation (aggregation, collections), derivation, counting.
        - Example: non-overlapping time periods, supplier cannot be their own customer.

- **OntoUML Conceptual Model** _(max. 20 points)_
    - Diagrams of the conceptual model + description _(max. 15 points)_
    - OCL constraints:
        - 3 non-trivial (as above)
        - At least 2 additional domain-relevant constraints _(max. 5 points)_
    - Evaluation is based on:
        - Model correctness
        - Use of OntoUML structural constructs

- **UML Transformed from OntoUML** _(max. 5 points)_
    - Evaluated based on completeness and correctness of the transformation.

---

### 2nd Part

- **BPMN Model of the Whole Process** _(max. 3 points)_

- **DEMO Models** _(max. 12 points)_
    - Minimum 5 ontological transactions
    - **Extended TPT** _(max. 8 points)_
        - ID, transaction kind, product kind, coordination acts (including revokes)
    - **OCD** _(max. 4 points)_
        - Based on TPT
        - Includes interstriction and external aggregated transactions

---

## Conditions and Requirements

- Each semester project must be **original**.
- It may be completed individually or in **pairs** (max. 2 members).
    - Teams are self-formed.
    - Recommended to use *pair programming* — working together at the same computer.
    - For remote collaboration, use version control (e.g., Git) and communication tools (e.g., MS Teams).
- In case of unequal contribution in a pair:
    - Each student is evaluated individually.
    - One member can receive **0 points** if they did not participate.

---

## Submission

- Submit as a **PDF** file containing all text and diagrams.
- Submission is done by one team member via [Moodle](https://moodle-vyuka.cvut.cz).
    - The second member must confirm the submission in Moodle.
- **Deadlines** follow the [official schedule](xref:schedule#).
    - Deadline is **Sunday at 23:59:59** of the given week.
    - Late submissions allowed **up to 1 week** with a penalty of **-5 points**.

---

## Evaluation of the Conceptual Model OntoUML

Conceptual model will be evaluated based on:

- **Correctness to the assignment**
- **Correct use of OntoUML concepts**

You can earn **up to 10 points** for correct usage of OntoUML concepts.

> ⚠️ If the submitted PDF is missing the **table of used OntoUML concepts**, you **automatically lose 5 points**.

| Concept             | Description                                                                 | Points |
|---------------------|-----------------------------------------------------------------------------|--------|
| **Kind**            | **Mandatory** – at least 2 different species                                | -      |
| SubKind             | At least 2 different subspecies of one species                              | 0.5    |
| Role                | At least 2 different roles                                                   | 0.5    |
| Phase               | At least 2 different phases                                                  | 0.5    |
| Category            | At least 1 category                                                          | 1      |
| RoleMixin           | At least 1 role mixin                                                        | 1      |
| PhaseMixin          | At least 1 phase mixin                                                       | 1      |
| Mixin               | At least 1 mixin                                                             | 1      |
| Functional Complex  | A unit composed of at least 2 components with different part duties          | 1      |
| Part                | At least 2 different obligations of the whole toward parts                  | 0.5    |
| Quantity            | At least 1 quantity                                                          | 0.5    |
| Collective          | At least 1 collective                                                        | 0.5    |
| Quality             | At least 1 quality                                                           | 0.5    |
| Mode                | At least 1 mode                                                              | 0.5    |
| Relator             | At least 2 relators for material relations (complete pattern)               | 0.5    |
| Formal Relation     | At least 1 formal relation                                                   | 0.5    |

**Additional 5 points**:
- **Syntactic and semantic correctness**
- **Readability**:
    - Avoid unnecessary line intersections.
    - Split large diagrams into smaller ones where appropriate.
    - Use consistent notation (e.g., `0..*`, `0..n`, `N`, `*`, etc.)

