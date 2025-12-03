public class HelloWorld {
  private static final String DEFAULT_GREETING = "Hello, World!";

  public static String hello(String name) {
    if (name == null || name.isEmpty()) {
      return DEFAULT_GREETING;
    }

    return "Hello, " + name + "!";
  }
}