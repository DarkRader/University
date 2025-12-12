
declare namespace Cypress {
    interface Chainable {
      login(email: string, password: string): Chainable<void>;
      confirmDocSubmission(): Chainable<void>;
      submitDoc(content: string, dsr: string): Chainable<void>
      generateUUID(): string;
      docExistsInGrid(targetTitle:string, shouldExist: boolean): Chainable<void>
      compareStringArrays(array1: string[], array2: string[]): Chainable<void>;
      generateRandomString(length: number): Chainable<string>;
    }
  }
  