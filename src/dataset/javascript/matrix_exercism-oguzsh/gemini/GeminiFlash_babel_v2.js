module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' for smaller bundle sizes if polyfills are needed.  False is often inefficient.
        modules: 'commonjs', // Specify module type for better tree shaking if possible.  Defaults to 'auto' which can be less efficient.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"],
};