module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: false,
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};