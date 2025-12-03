class HelloWorld {
  private static readonly DEFAULT_NAME = 'World';
  private static readonly GREETING = 'Hello, ';
  private static readonly EXCLAMATION = '!';

  static hello(name: string = HelloWorld.DEFAULT_NAME): string {
    return HelloWorld.GREETING + name + HelloWorld.EXCLAMATION;
  }
}

export default HelloWorld;