describe('registration', () => {

    it('TC:003 Should not be able to register with invalid email format',()=>{

      const registerUrl = Cypress.env('REGISTRATION_URL');
      cy.visit(registerUrl)
      cy.wait(3000)

      cy.get('#input_first_name').type('x')
      cy.get('#input_last_name').type('x')
      cy.get('#input_username').type('x')
      cy.get('#input_password').type('x')
      cy.get('#input_email').type('x')
      cy.get('#btn_register').click()
      cy.wait(3000)

      cy.on('window:alert', (alertText) => {
        expect(alertText).to.include('OPERATION NOT SUCCESSFUL');
      });
    })
  
  })