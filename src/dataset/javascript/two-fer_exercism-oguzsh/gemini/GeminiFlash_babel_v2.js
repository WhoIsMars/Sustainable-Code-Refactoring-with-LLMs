module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but only if necessary.
        modules: 'commonjs', // Explicitly set modules to commonjs for Node.js environment.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"], // Keep this if bigint syntax is actually used.  Remove if not.
};