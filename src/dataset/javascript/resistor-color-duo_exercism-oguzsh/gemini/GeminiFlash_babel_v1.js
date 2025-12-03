module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or the minimum Node.js version you support
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed
        modules: 'commonjs', // or false if you are using native ES modules
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};