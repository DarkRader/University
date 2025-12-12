describe('evaluation', () => {

  it('TC:007 Should post evaluation', () => {
    cy.login('test','test')

    cy.get('#btn_submit_doc').click()
    cy.wait(3000)

    const docContent: string = generateRandomString(5)
    cy.submitDoc(docContent,'dsr-34b7e65c-c19a-4218-827e-9d184fc49f8b')
    cy.wait(3000)

    cy.go(-1)
    cy.get('#btn_go_to_docs').click()
    cy.wait(3000)

    cy.get('.text-1').each(($element) => {
      cy.wrap($element).invoke('text').then((title) => {
        const trimmedTitle = title.trim(); 
        if (trimmedTitle === docContent) {
          cy.wrap($element).click(); 
        }
      });
    });
    cy.wait(3000)

    cy.get('#btn_post_eval').click()
    cy.wait(3000)

    cy.get('#btn_see_eval').click()
    cy.wait(3000)

    cy.get('.mat-mdc-table.mdc-data-table__table')
    .find('tbody tr') 
    .its('length')
    .should('eq', 1);

    
  })

  function generateRandomString(length: number): string {
    const characters: string = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    let randomString: string = '';
  
    for (let i = 0; i < length; i++) {
      const randomIndex: number = Math.floor(Math.random() * characters.length);
      randomString += characters.charAt(randomIndex);
    }
  
    return randomString;
  }

})