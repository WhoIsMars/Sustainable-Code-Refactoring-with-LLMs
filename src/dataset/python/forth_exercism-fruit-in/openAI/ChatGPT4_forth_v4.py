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
                self._define(ops)
            else:
                self._stack.append(int(op))

    def _define(self, ops):
        try:
            end_idx = ops.index(";")
        except ValueError:
            raise ValueError(r".+")
        definition = ops[:end_idx]
        if len(definition) < 2 or definition[0].isdigit():
            raise ValueError(r".+")
        self._definitions[definition[0]] = " ".join(
            self._definitions.get(op, op) for op in definition[1:]
        )
        del ops[:end_idx + 1]

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