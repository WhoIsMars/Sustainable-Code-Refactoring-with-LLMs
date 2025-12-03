module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: { node: 'current' },
        useBuiltIns: 'entry',
        corejs: 3,
      },
    ],
  ],
};