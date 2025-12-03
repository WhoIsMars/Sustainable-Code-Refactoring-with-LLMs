module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but only if necessary.
        modules: 'commonjs', // Explicitly set modules to commonjs if that's the target.  Avoids auto-detection overhead.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"], // Keep this if bigint syntax is actually used.  Remove if not.
  exclude: [/node_modules/], // Exclude node_modules from babel processing.
};