class Forth:

    def __init__(self):
        self._stack = []
        self._definitions = {}
        self._operators = {
            "+": self.add,
            "-": self.sub,
            "*": self.mul,
            "/": self.div,
            "dup": self.dup,
            "drop": self.drop,
            "swap": self.swap,
            "over": self.over,
        }

    def stack(self):
        return self._stack

    def eval(self, data):
        ops = data.lower().split()

        for op in ops:
            if op in self._definitions:
                self.eval(self._definitions[op])
            elif op in self._operators:
                self._operators[op]()
            elif op == ":":
                self.define_word(ops)
                break
            else:
                try:
                    self._stack.append(int(op))
                except ValueError:
                    raise ValueError(r".+")

    def define_word(self, ops):
        try:
            colon_index = ops.index(":")
            semicolon_index = ops.index(";")
        except ValueError:
            raise ValueError(r".+")

        if colon_index >= semicolon_index or semicolon_index - colon_index < 2:
            raise ValueError(r".+")

        new_word = ops[colon_index + 1]
        if not new_word.isidentifier() or new_word.isdigit():
            raise ValueError(r".+")

        definition = " ".join(ops[colon_index + 2:semicolon_index])
        self._definitions[new_word] = definition
        del ops[colon_index:semicolon_index + 1]

    def define(self, ops):
        word_name = ops[0]
        definition_parts = []
        for i in range(1, len(ops)):
            op = ops[i]
            if op in self._definitions:
                definition_parts.append(self._definitions[op])
            else:
                try:
                    int(op)
                    definition_parts.append(op)
                except ValueError:
                    definition_parts.append(op)
        self._definitions[word_name] = " ".join(definition_parts)

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
        self._stack[-1], self._stack[-2] = self._stack[-2], self._stack[-1]

    def over(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        self._stack.append(self._stack[-2])

    def add(self):
        try:
            self._stack.append(self._stack.pop() + self._stack.pop())
        except IndexError:
            raise StackUnderflowError(r".+")

    def sub(self):
        try:
            y = self._stack.pop()
            x = self._stack.pop()
            self._stack.append(x - y)
        except IndexError:
            raise StackUnderflowError(r".+")

    def mul(self):
        try:
            self._stack.append(self._stack.pop() * self._stack.pop())
        except IndexError:
            raise StackUnderflowError(r".+")

    def div(self):
        try:
            y = self._stack.pop()
            x = self._stack.pop()
            if y == 0:
                raise ZeroDivisionError(r".+")
            self._stack.append(x // y)
        except IndexError:
            raise StackUnderflowError(r".+")

    def pop2(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        return (self._stack.pop(), self._stack.pop())


def evaluate(input_data):
    forth = Forth()
    for data in input_data:
        forth.eval(data)
    return forth.stack()


class StackUnderflowError(Exception):
    pass