module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  Avoids "current" which can be less predictable.
        },
        useBuiltIns: false, // Consider "usage" or "entry" if polyfills are needed, but only if necessary.  False is most efficient if no polyfills are required.
        modules: false, // Prevents Babel from transforming modules, allowing webpack or other bundlers to handle it (more efficient).
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"] // Keep this if bigint syntax is actually used.  Remove if not.
};