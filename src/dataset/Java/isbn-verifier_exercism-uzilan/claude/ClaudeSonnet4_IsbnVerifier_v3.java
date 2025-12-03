import java.util.stream.IntStream;

class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String cleaned = stringToVerify.replace("-", "");
        
        if (cleaned.length() != 10) {
            return false;
        }
        
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            char c = cleaned.charAt(i);
            int digit;
            
            if (i < 9) {
                if (c < '0' || c > '9') {
                    return false;
                }
                digit = c - '0';
            } else {
                if (c == 'X') {
                    digit = 10;
                } else if (c >= '0' && c <= '9') {
                    digit = c - '0';
                } else {
                    return false;
                }
            }
            
            sum += digit * (10 - i);
        }
        
        return sum % 11 == 0;
    }

    private java.util.List<String> removeHyphens(String stringToVerify) {
        return stringToVerify.replaceAll("-", "")
                .codePoints()
                .mapToObj(c -> "" + (char) c)
                .collect(java.util.stream.Collectors.toList());
    }

    private boolean checkCharacters(java.util.List<String> noHyphens) {
        return noHyphens.size() == 10 &&
                noHyphens.subList(0, 9).stream().noneMatch(i -> i.matches("\\D"));
    }

    private boolean checkLastChar(String last) {
        return last.matches("\\d") || last.equals("X");
    }

    private java.util.List<Integer> convertToIntegers(java.util.List<String> noHyphens, String last) {
        final java.util.List<Integer> integers = noHyphens.subList(0, 9).stream()
                .map(Integer::parseInt)
                .collect(java.util.stream.Collectors.toList());

        integers.add(last.equals("X") ? 10 : Integer.parseInt(last));
        return integers;
    }

    private int calculateSum(java.util.List<Integer> integers) {
        return IntStream.rangeClosed(1, 10)
                .boxed()
                .sorted(java.util.Comparator.reverseOrder())
                .mapToInt(i -> integers.get(i - 1) * i)
                .sum();
    }
}