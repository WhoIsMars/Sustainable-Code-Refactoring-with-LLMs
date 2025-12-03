import java.util.*;

public class ForthEvaluator {

    private final Stack<Integer> stack = new Stack<>();
    private final Map<String, List<String>> userDefinedOperators = new HashMap<>();

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
            try {
                int number = Integer.parseInt(operator);
                stack.push(number);
            } catch (NumberFormatException e) {
                applyOperator(operator);
            }
        }
    }

    private void applyOperator(String operator) {
        String lowercaseOperator = operator.toLowerCase();
        List<String> userOperator = userDefinedOperators.get(lowercaseOperator);
        if (userOperator != null) {
            applyOperators(userOperator.toArray(new String[0]));
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
                        String.format("No definition available for operator \"%s\"", lowercaseOperator));
        }
    }

    private void add() {
        expectNumberOfValuesInTheStack(2, "Addition");
        stack.push(stack.pop() + stack.pop());
    }

    private void subtract() {
        expectNumberOfValuesInTheStack(2, "Subtraction");
        int subtrahend = stack.pop();
        int minuend = stack.pop();
        stack.push(minuend - subtrahend);
    }

    private void multiply() {
        expectNumberOfValuesInTheStack(2, "Multiplication");
        stack.push(stack.pop() * stack.pop());
    }

    private void divide() {
        expectNumberOfValuesInTheStack(2, "Division");
        int denominator = stack.pop();
        expectNoZeroDenominator(denominator);
        int numerator = stack.pop();
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
        String operatorName = split[1];
        expectNoNumberRedefinition(operatorName);
        List<String> operatorList = new ArrayList<>(Arrays.asList(split).subList(2, split.length - 1));
        userDefinedOperators.put(operatorName.toLowerCase(), operatorList);
    }

    private void expectNumberOfValuesInTheStack(int number, String operation) {
        if (stack.size() < number) {
            throw new IllegalArgumentException(
                    String.format(
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
        try {
            Integer.parseInt(operator);
            throw new IllegalArgumentException("Cannot redefine numbers");
        } catch (NumberFormatException ignored) {
            // It's not a number, so it's ok
        }
    }
}