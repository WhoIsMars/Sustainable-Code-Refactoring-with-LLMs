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
        loose: true,
        bugfixes: true,
        exclude: ['transform-regenerator']
      },
    ],
  ],
  plugins: ["@babel/plugin-syntax-bigint"]
};