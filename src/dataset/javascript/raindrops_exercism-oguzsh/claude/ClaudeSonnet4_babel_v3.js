module.exports = {
  presets: [
    [
      '@babel/preset-env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: false,
        loose: true,
        bugfixes: true,
      },
    ],
  ],
  plugins: ['@babel/plugin-syntax-bigint'],
};