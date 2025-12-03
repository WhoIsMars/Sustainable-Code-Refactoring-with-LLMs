module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' forces transpilation.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are truly needed.  False is most efficient if not.
        modules: 'commonjs', // Explicitly set modules to commonjs if that's the target.  Avoids auto-detection overhead.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};