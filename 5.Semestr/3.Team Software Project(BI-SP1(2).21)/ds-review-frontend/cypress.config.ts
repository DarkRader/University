import { defineConfig } from "cypress";

export default defineConfig({
  env: {
    BASE_URL: 'http://localhost:4200/',
    SUBMIT_DOC_URL: 'http://localhost:4200/documents/submit/',
    REGISTRATION_URL: 'http://localhost:4200/registration'
  },
  e2e: {
    setupNodeEvents(on, config) {
      // implement node event listeners here
    },
  },
});
