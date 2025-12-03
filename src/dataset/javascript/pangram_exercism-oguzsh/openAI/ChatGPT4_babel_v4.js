module.exports = {
  presets: [
    [
      '@babel/env',
      {
        targets: { node: 'current' },
        bugfixes: true,
        shippedProposals: true,
      },
    ],
  ],
  plugins: ['@babel/plugin-syntax-bigint'],
};