module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or a more specific, modern Node.js version
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed
        modules: 'commonjs', // Explicitly set module type
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};