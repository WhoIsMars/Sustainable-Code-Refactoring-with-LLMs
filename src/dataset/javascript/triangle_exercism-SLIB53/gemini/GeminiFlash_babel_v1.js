module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // or false if you handle modules externally
      },
    ],
  ],
  plugins: [], // Add any necessary plugins here
};