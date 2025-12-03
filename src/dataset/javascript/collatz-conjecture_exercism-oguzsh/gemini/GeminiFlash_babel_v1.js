module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: '16', // Or the lowest supported Node.js version
        },
        useBuiltIns: false,
        modules: 'commonjs', // Explicitly set modules to commonjs
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};