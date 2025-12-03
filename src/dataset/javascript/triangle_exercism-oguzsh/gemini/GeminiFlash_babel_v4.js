module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs',
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};