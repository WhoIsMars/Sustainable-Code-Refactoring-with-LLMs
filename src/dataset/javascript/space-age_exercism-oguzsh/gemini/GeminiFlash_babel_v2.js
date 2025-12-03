module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' for smaller bundles if polyfills are needed.  False is fastest if no polyfills are needed.
        modules: false, // Enable tree-shaking by preventing Babel from transforming modules.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};