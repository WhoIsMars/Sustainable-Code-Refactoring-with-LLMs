import java.util.*;

import static java.lang.Integer.parseInt;
import static java.lang.String.format;

public class ForthEvaluator {

    private final ArrayDeque<Integer> stack = new ArrayDeque<>();
    private final Map<String, String[]> userDefinedOperators = new HashMap<>();

    public List<Integer> evaluateProgram(List<String> inputList) {
        for (String input : inputList) {
            if (input.startsWith(":")) {
                addUserDefinedOperator(input);
            } else {
                applyOperators(input.split(" "));
            }
        }
        return new ArrayList<>(stack);
    }

    private void applyOperators(String[] operators) {
        for (String operator : operators) {
            if (isNumeric(operator)) {
                stack.push(parseInt(operator));
            } else {
                applyOperator(operator);
            }
        }
    }

    private void applyOperator(String operator) {
        final String lowercaseOperator = operator.toLowerCase();
        if (userDefinedOperators.containsKey(lowercaseOperator)) {
            applyOperators(userDefinedOperators.get(lowercaseOperator));
            return;
        }

        switch (lowercaseOperator) {
            case "+":
                add();
                break;
            case "-":
                subtract();
                break;
            case "*":
                multiply();
                break;
            case "/":
                divide();
                break;
            case "dup":
                duplicate();
                break;
            case "drop":
                drop();
                break;
            case "swap":
                swap();
                break;
            case "over":
                over();
                break;
            default:
                throw new IllegalArgumentException(
                        format("No definition available for operator \"%s\"", lowercaseOperator));
        }
    }

    private void add() {
        expectNumberOfValuesInTheStack(2, "Addition");
        int b = stack.pop();
        int a = stack.pop();
        stack.push(a + b);
    }

    private void subtract() {
        expectNumberOfValuesInTheStack(2, "Subtraction");
        int subtrahend = stack.pop();
        int minuend = stack.pop();
        stack.push(minuend - subtrahend);
    }

    private void multiply() {
        expectNumberOfValuesInTheStack(2, "Multiplication");
        int b = stack.pop();
        int a = stack.pop();
        stack.push(a * b);
    }

    private void divide() {
        expectNumberOfValuesInTheStack(2, "Division");
        final int denominator = stack.pop();
        expectNoZeroDenominator(denominator);
        final int numerator = stack.pop();
        stack.push(numerator / denominator);
    }

    private void duplicate() {
        expectNumberOfValuesInTheStack(1, "Duplicating");
        stack.push(stack.peek());
    }

    private void drop() {
        expectNumberOfValuesInTheStack(1, "Dropping");
        stack.pop();
    }

    private void swap() {
        expectNumberOfValuesInTheStack(2, "Swapping");
        final int last = stack.pop();
        final int lastButOne = stack.pop();
        stack.push(last);
        stack.push(lastButOne);
    }

    private void over() {
        expectNumberOfValuesInTheStack(2, "Overing");
        final int last = stack.pop();
        final int lastButOne = stack.peek();
        stack.push(last);
        stack.push(lastButOne);
    }

    private void addUserDefinedOperator(String input) {
        final String[] split = input.split(" ");
        expectNoNumberRedefinition(split[1]);
        String[] definition = new String[split.length - 3];
        System.arraycopy(split, 2, definition, 0, definition.length);
        userDefinedOperators.put(split[1].toLowerCase(), definition);
    }

    private boolean isNumeric(String operator) {
        if (operator.isEmpty()) return false;
        for (int i = 0; i < operator.length(); i++) {
            if (!Character.isDigit(operator.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    private void expectNumberOfValuesInTheStack(int number, String operation) {
        if (stack.size() < number) {
            throw new IllegalArgumentException(
                    format(
                            "%s requires that the stack contain at least %d values",
                            operation,
                            number));
        }
    }

    private void expectNoZeroDenominator(int number) {
        if (number == 0) {
            throw new IllegalArgumentException("Division by 0 is not allowed");
        }
    }

    private void expectNoNumberRedefinition(String operator) {
        if (isNumeric(operator)) {
            throw new IllegalArgumentException("Cannot redefine numbers");
        }
    }
}