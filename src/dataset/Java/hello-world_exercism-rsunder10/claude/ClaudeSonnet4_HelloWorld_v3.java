public class HelloWorld {
  private static final String DEFAULT_GREETING = "Hello, World!";
  private static final String GREETING_PREFIX = "Hello, ";
  private static final String GREETING_SUFFIX = "!";
  
  public static String hello(String name) {
    if (name == null || name.isEmpty()) {
      return DEFAULT_GREETING;
    }
    
    return new StringBuilder(GREETING_PREFIX.length() + name.length() + GREETING_SUFFIX.length())
        .append(GREETING_PREFIX)
        .append(name)
        .append(GREETING_SUFFIX)
        .toString();
  }
}