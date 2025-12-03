module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' forces transpilation.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are truly needed, but benchmark first.
        modules: 'commonjs', // Explicitly set module type.  If not needed, set to false.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"], // Keep this if bigint syntax is actually used.
};