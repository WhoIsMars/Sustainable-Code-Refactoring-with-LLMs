module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: { node: 'current' },
        useBuiltIns: false,
        bugfixes: true,
        modules: false,
      },
    ],
  ],
};