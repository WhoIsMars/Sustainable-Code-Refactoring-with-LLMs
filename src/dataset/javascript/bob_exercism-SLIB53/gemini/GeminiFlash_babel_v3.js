module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: 'entry',
        corejs: { version: 3, proposals: true },
        modules: 'commonjs',
      },
    ],
  ],
};