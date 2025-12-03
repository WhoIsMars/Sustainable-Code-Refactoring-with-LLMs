module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version. 'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but only if necessary.
        modules: 'commonjs', // Explicitly set module type if needed.  Avoid 'auto' for slight perf gain.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"],
  exclude: [/node_modules/], // Exclude node_modules from Babel processing
};