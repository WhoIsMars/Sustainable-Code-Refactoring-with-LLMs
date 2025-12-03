module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // Explicitly set modules to commonjs for node
      },
    ],
  ],
  plugins: [], // Add an empty plugins array for explicitness and future use.
};