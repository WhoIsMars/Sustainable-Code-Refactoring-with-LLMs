module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // Or 'amd', 'umd', 'systemjs', or false
      },
    ],
  ],
  plugins: [],
};