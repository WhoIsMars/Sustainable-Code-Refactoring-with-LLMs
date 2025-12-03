module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: {
          node: 'current',
        },
        useBuiltIns: false,
        modules: 'commonjs', // Or 'amd', 'umd', 'systemjs', 'auto' if needed
      },
    ],
  ],
  plugins: [], // Explicitly define plugins array, even if empty
};