describe('document', () => {

  it('TC:004 Newly created document should appear in All Documents', () => {
    cy.login('test','test')

    cy.get('#btn_submit_doc').click()
    cy.wait(3000)

    const content = generateRandomString(5)
    cy.get('#input_doc_text').type(content)
    cy.get('#input_dsr_token').type('dsr-34b7e65c-c19a-4218-827e-9d184fc49f8b')
    cy.get('#btn_submit_doc').click()
    cy.wait(3000)

    cy.go(-1)

    cy.get('#btn_go_to_docs').click()
    cy.wait(3000)

    cy.docExistsInGrid(content,true)
  });
  
  it('TC:005 Should not submit document when invalid dsr-token provided', ()=>{
    cy.login('test','test')

    cy.get('#btn_submit_doc').click()
    cy.wait(3000)

    const content = 'invalid'
    cy.submitDoc(content, 'invalid')
    cy.wait(3000)

    cy.go(-1)

    cy.get('#btn_go_to_docs').click()
    cy.wait(3000)

    cy.docExistsInGrid(content,false)
  })

  it('TC:006 Table should contain same doc titles as grid', ()=>{
    cy.login('test','test')

    cy.get('#btn_go_to_docs').click()
    cy.wait(3000)
    
    let titlesGrid: string[] = []
    cy.get('.text-1').each(($element) => {
      cy.wrap($element).invoke('text').then((title) => {
        const trimmedTitle = title.trim(); // Trim the title
        titlesGrid.push(trimmedTitle)
      });
    })

    cy.get('#btn_switch').click()
    cy.wait(3000)

    let titlesTable: string[] = []
    cy.get('.mat-mdc-cell.mdc-data-table__cell.cdk-cell.cdk-column-title').each(($element) => {
      cy.wrap($element).invoke('text').then((title) => {
        const trimmedTitle = title.trim(); // Trim the title
        titlesTable.push(trimmedTitle)
      });
    })

    cy.compareStringArrays(titlesGrid, titlesTable);
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