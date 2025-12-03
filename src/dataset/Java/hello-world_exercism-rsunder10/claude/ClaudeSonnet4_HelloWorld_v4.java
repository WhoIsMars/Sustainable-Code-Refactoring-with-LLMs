public class HelloWorld {
  private static final String HELLO_PREFIX = "Hello, ";
  private static final String HELLO_WORLD = "Hello, World!";
  private static final String EXCLAMATION = "!";
  
  public static String hello(String name) {
    if (name == null || name.isEmpty()) {
      return HELLO_WORLD;
    }
    
    return new StringBuilder(HELLO_PREFIX.length() + name.length() + 1)
        .append(HELLO_PREFIX)
        .append(name)
        .append(EXCLAMATION)
        .toString();
  }
}