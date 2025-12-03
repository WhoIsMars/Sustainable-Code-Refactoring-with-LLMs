module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or a more specific, supported version. 'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' for targeted polyfills if needed.
        modules: 'commonjs', // Explicitly set module type if needed, often defaults to 'auto' which can add overhead.
      },
    ],
  ],
  plugins: [], // Add plugins here if needed.  Empty array is more explicit than omitting.
};