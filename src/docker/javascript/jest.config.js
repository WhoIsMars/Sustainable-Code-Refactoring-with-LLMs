// jest.config.js
export default {
  transform: {},
  moduleNameMapper: {
    "\\.(css|less|sass|scss)$": "identity-obj-proxy",
  },
  testEnvironment: "node",
  // CRITICAL FIX: Include testSuite pattern for JavaScript tests
  testMatch: [
    "**/*.test.js",
    "**/*.test.ts",
    "**/*.spec.js",
    "**/*.spec.ts",
    "**/*testSuite.js",   // Pattern for JavaScript testSuite files
    "**/*testSuite.ts",
    "**/*_testSuite.js",  // Alternative naming pattern
    "**/*_testSuite.ts"
  ],
};
