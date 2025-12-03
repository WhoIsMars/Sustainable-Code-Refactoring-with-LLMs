export default class HelloWorld {
  private constructor() {}

  static hello(name = 'World'): string {
    return `Hello, ${name}!`;
  }
}