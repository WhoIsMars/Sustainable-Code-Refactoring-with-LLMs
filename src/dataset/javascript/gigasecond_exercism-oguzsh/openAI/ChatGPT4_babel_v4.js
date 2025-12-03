module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: { node: 'current' },
        useBuiltIns: false,
        bugfixes: true,
      },
    ],
  ],
  plugins: ['@babel/plugin-syntax-bigint'],
};