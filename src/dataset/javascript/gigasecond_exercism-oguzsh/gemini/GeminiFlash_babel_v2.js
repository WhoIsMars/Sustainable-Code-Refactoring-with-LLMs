module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '14', // Or a more specific, supported version.  'current' can be inefficient.
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' for smaller bundles if polyfills are needed.  False is often inefficient.
        modules: 'commonjs', // Explicitly set module type.  Avoids auto-detection overhead.
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"],
  exclude: [/node_modules/], // Exclude node_modules from Babel processing
};