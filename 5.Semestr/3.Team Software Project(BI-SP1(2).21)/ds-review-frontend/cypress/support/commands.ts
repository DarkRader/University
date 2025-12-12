/// <reference types="cypress" />

Cypress.Commands.add('login', (username, password) => {
    const baseUrl = Cypress.env('BASE_URL');
    cy.visit(baseUrl)
    cy.get('#input_username').type(username)
    cy.get('#input_password').type(password)
    cy.get('#btn_login').click()
});

Cypress.Commands.add('confirmDocSubmission', () => {
  cy.window().then((win) => {
    cy.stub(win, 'alert').as('windowAlert');
  });

  cy.get('@windowAlert').should('have.been.calledWith', 'SUCCESSFULLY SUBMITTED');
} )

Cypress.Commands.add('submitDoc',(content: string, dsr: string) => {
    cy.get('#input_doc_text').type(content)
    cy.get('#input_dsr_token').type(dsr)
    cy.get('#btn_submit_doc').click()
})

Cypress.Commands.add('docExistsInGrid',(targetTitle:string, shouldExist: boolean) => {
    let docExists = false;
    cy.get('.text-1').each(($element) => {
      cy.wrap($element).invoke('text').then((title) => {
        const trimmedTitle = title.trim(); // Trim the title
        
        if (trimmedTitle === targetTitle) {
          docExists = true;
        }
        console.log(trimmedTitle + ' ' + targetTitle + ' ' + docExists)
      });
    }).then(() => {
      cy.wrap(docExists).should('eq', shouldExist);
    });   
})
  
Cypress.Commands.add('compareStringArrays', (array1, array2) => {
  // Sort the arrays to ensure order doesn't affect the comparison
  const sortedArray1 = array1.slice().sort();
  const sortedArray2 = array2.slice().sort();

  // Use deep equality check to compare arrays
  expect(sortedArray1).to.deep.equal(sortedArray2);
});

