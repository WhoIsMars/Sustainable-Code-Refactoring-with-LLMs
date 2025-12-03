module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // Explicitly set modules to commonjs
      },
    ],
  ],
  plugins: [], // Add an empty plugins array for explicitness and potential future use
};