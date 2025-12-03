module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version. 'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but benchmark first.
        modules: 'commonjs', // Explicitly set module type if needed, often defaults to commonjs.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"], // Keep this if bigint syntax is actually used.
};