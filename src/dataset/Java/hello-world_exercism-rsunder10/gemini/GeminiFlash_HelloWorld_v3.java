public class HelloWorld {
  public static String hello(String name) {
    if (name == null || name.isEmpty()) {
      return "Hello, World!";
    }

    return new StringBuilder("Hello, ").append(name).append("!").toString();
  }
}