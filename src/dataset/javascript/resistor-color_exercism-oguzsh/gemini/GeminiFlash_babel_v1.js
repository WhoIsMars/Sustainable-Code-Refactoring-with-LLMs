module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or the lowest Node.js version you need to support
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed
        modules: 'commonjs', // Or 'auto' if you want Babel to handle module transformation
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};