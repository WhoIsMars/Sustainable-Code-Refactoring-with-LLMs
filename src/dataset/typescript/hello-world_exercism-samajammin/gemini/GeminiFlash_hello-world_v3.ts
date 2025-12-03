class HelloWorld {
  private static readonly DEFAULT_NAME = 'World';

  static hello(name: string = HelloWorld.DEFAULT_NAME): string {
    const targetName = name || HelloWorld.DEFAULT_NAME;
    return `Hello, ${targetName}!`;
  }
}

export default HelloWorld;