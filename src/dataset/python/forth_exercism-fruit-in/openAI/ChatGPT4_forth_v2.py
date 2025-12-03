class Forth:

    def __init__(self):
        self._stack = []
        self._definitions = {}

    def stack(self):
        return self._stack

    def eval(self, data):
        ops = data.lower().split()

        while ops:
            op = ops.pop(0)

            if op in self._definitions:
                self.eval(self._definitions[op])
            elif op in {"+", "-", "*", "/", "dup", "drop", "swap", "over"}:
                getattr(self, op)()
            elif op == ":":
                self.define(ops)
            else:
                self._stack.append(int(op))

    def define(self, ops):
        if ";" not in ops:
            raise ValueError(r".+")
        semicolon_index = ops.index(";")
        definition = ops[:semicolon_index]
        if len(definition) < 2 or not definition[0].isalpha():
            raise ValueError(r".+")
        name, body = definition[0], definition[1:]
        for i, token in enumerate(body):
            if token in self._definitions:
                body[i] = self._definitions[token]
            elif token not in {"+", "-", "*", "/", "dup", "drop", "swap", "over"}:
                try:
                    int(token)
                except ValueError:
                    raise ValueError(r".+")
        self._definitions[name] = " ".join(body)
        del ops[:semicolon_index + 1]

    def dup(self):
        if not self._stack:
            raise StackUnderflowError(r".+")
        self._stack.append(self._stack[-1])

    def drop(self):
        if not self._stack:
            raise StackUnderflowError(r".+")
        self._stack.pop()

    def swap(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        self._stack[-2], self._stack[-1] = self._stack[-1], self._stack[-2]

    def over(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        self._stack.append(self._stack[-2])

    def add(self):
        self._binary_op(lambda x, y: y + x)

    def sub(self):
        self._binary_op(lambda x, y: y - x)

    def mul(self):
        self._binary_op(lambda x, y: y * x)

    def div(self):
        self._binary_op(lambda x, y: y // x if x != 0 else self._raise_zero_division())

    def _binary_op(self, operation):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        x, y = self._stack.pop(), self._stack.pop()
        self._stack.append(operation(x, y))

    def _raise_zero_division(self):
        raise ZeroDivisionError(r".+")


def evaluate(input_data):
    forth = Forth()
    for data in input_data:
        forth.eval(data)
    return forth.stack()


class StackUnderflowError(Exception):
    pass