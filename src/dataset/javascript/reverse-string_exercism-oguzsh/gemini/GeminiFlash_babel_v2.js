module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' forces transpilation.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but benchmark.
        modules: 'commonjs', // Explicitly set module type if needed.  Avoids auto-detection overhead.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"], // Keep this if bigint syntax is actually used.
};