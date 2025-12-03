import java.util.*;

import static java.lang.Integer.parseInt;
import static java.lang.String.format;

public class ForthEvaluator {

    private final Deque<Integer> stack = new ArrayDeque<>();
    private final Map<String, List<String>> userDefinedOperators = new HashMap<>();

    public List<Integer> evaluateProgram(List<String> inputList) {
        for (String input : inputList) {
            if (input.startsWith(":")) {
                addUserDefinedOperator(input);
            } else {
                applyOperators(Arrays.asList(input.split(" ")));
            }
        }
        return new ArrayList<>(stack);
    }

    private void applyOperators(List<String> operators) {
        for (String operator : operators) {
            if (isNumeric(operator)) {
                stack.push(parseInt(operator));
            } else {
                applyOperator(operator);
            }
        }
    }

    private void applyOperator(String operator) {
        String lowercaseOperator = operator.toLowerCase();
        List<String> userOperator = userDefinedOperators.get(lowercaseOperator);
        if (userOperator != null) {
            applyOperators(userOperator);
            return;
        }

        switch (lowercaseOperator) {
            case "+" -> add();
            case "-" -> subtract();
            case "*" -> multiply();
            case "/" -> divide();
            case "dup" -> duplicate();
            case "drop" -> drop();
            case "swap" -> swap();
            case "over" -> over();
            default -> throw new IllegalArgumentException(
                    format("No definition available for operator \"%s\"", lowercaseOperator));
        }
    }

    private void add() {
        expectNumberOfValuesInTheStack(2, "Addition");
        stack.push(stack.pop() + stack.pop());
    }

    private void subtract() {
        expectNumberOfValuesInTheStack(2, "Subtraction");
        int subtrahend = stack.pop();
        stack.push(stack.pop() - subtrahend);
    }

    private void multiply() {
        expectNumberOfValuesInTheStack(2, "Multiplication");
        stack.push(stack.pop() * stack.pop());
    }

    private void divide() {
        expectNumberOfValuesInTheStack(2, "Division");
        int denominator = stack.pop();
        expectNoZeroDenominator(denominator);
        stack.push(stack.pop() / denominator);
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
        int last = stack.pop();
        int lastButOne = stack.pop();
        stack.push(last);
        stack.push(lastButOne);
    }

    private void over() {
        expectNumberOfValuesInTheStack(2, "Overing");
        int last = stack.pop();
        int lastButOne = stack.peek();
        stack.push(last);
        stack.push(lastButOne);
    }

    private void addUserDefinedOperator(String input) {
        String[] split = input.split(" ");
        expectNoNumberRedefinition(split[1]);
        userDefinedOperators.put(
                split[1].toLowerCase(),
                Arrays.asList(split).subList(2, split.length - 1));
    }

    private boolean isNumeric(String operator) {
        int len = operator.length();
        if (len == 0) return false;
        for (int i = 0; i < len; i++) {
            if (!Character.isDigit(operator.charAt(i))) return false;
        }
        return true;
    }

    private void expectNumberOfValuesInTheStack(int number, String operation) {
        if (stack.size() < number) {
            throw new IllegalArgumentException(
                    format("%s requires that the stack contain at least %d values", operation, number));
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