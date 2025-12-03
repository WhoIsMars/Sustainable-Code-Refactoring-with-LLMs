module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or the lowest Node.js version you support
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed
        modules: 'commonjs', // Explicitly set module type
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};