module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: { node: 'current' },
        bugfixes: true,
        modules: false,
      },
    ],
  ],
  plugins: ['@babel/plugin-syntax-bigint'],
};