module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or the minimum Node.js version you support
        },
        useBuiltIns: false, // Consider 'usage' or 'entry' if polyfills are needed, but benchmark first
        modules: 'commonjs', // Explicitly set modules to commonjs if that's what you need
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};