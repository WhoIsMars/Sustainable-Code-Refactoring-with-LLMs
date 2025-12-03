module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // Explicitly set modules to commonjs for Node.js
      },
    ],
  ],
  plugins: [
    '@babel/plugin-transform-runtime' // Add runtime transform to avoid inline helpers
  ]
};