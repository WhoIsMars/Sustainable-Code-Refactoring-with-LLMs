module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' for smaller bundle sizes if polyfills are needed.  False is often inefficient.
        modules: 'commonjs', // Explicitly set modules to commonjs for node.  Avoids auto-detection overhead.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"],
  exclude: [/node_modules/], // Exclude node_modules from babel processing.
};