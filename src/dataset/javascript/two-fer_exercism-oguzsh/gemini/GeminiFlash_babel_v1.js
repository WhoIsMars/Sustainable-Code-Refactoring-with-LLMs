module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or a more specific, supported version. 'current' can lead to inconsistencies.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but benchmark first.
        modules: 'commonjs', // Explicitly set module type for clarity and potential optimization.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};