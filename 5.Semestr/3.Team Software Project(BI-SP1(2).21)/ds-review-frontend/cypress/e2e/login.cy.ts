describe('template spec', () => {

  it('TC:000 Should log in and check user data in usermap', () => {
    cy.login('test','test')

    cy.wait(3000)

    cy.get('#username').should('have.text', 'test');
    cy.get('#first_name').should('have.text', 'test_first_name');
    cy.get('#last_name').should('have.text','test_last_name')
    cy.get('#dsr_token').should('have.text','dsr-34b7e65c-c19a-4218-827e-9d184fc49f8b')

  })

  it('TC:001 Should not be able to return to login page with back arrow after login.',()=>{
    cy.login('test','test')

    cy.wait(3000)

    cy.get('#btn_logout').click()

    cy.wait(3000)

    cy.go(-1);
    const baseUrl = Cypress.env('BASE_URL');
    cy.url().should('eq', baseUrl);
  })

  it('TC:002 Should not be able to return to login page with forward arrow after login.',()=>{
    cy.login('test','test')

    cy.wait(3000)

    cy.get('#btn_logout').click()

    cy.wait(3000)

    cy.go(+1);
    const baseUrl = Cypress.env('BASE_URL');
    cy.url().should('eq', baseUrl);
  })

})