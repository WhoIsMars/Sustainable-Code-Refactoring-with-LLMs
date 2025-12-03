class Forth:

    def __init__(self):
        self._stack = []
        self._definitions = {}
        self._operations = {
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

        i = 0
        while i < len(ops):
            op = ops[i]

            if op in self._definitions:
                self.eval(self._definitions[op])
            elif op in self._operations:
                self._operations[op]()
            elif op == ":":
                i += 1
                if i >= len(ops):
                    raise ValueError(r".+")
                
                definition_name = ops[i]
                i += 1
                
                if i >= len(ops):
                    raise ValueError(r".+")

                if not definition_name.isidentifier() or definition_name[0].isdigit():
                    raise ValueError(r".+")
                
                definition_body = []
                while i < len(ops) and ops[i] != ";":
                    definition_body.append(ops[i])
                    i += 1
                
                if i >= len(ops) or ops[i] != ";":
                    raise ValueError(r".+")
                
                self._definitions[definition_name] = " ".join(definition_body)
            else:
                try:
                    self._stack.append(int(op))
                except ValueError:
                    raise ValueError(r".+")
            i += 1

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
            self._stack[-2] += self._stack[-1]
            self._stack.pop()
        except IndexError:
            raise StackUnderflowError(r".+")

    def sub(self):
        try:
            self._stack[-2] -= self._stack[-1]
            self._stack.pop()
        except IndexError:
            raise StackUnderflowError(r".+")

    def mul(self):
        try:
            self._stack[-2] *= self._stack[-1]
            self._stack.pop()
        except IndexError:
            raise StackUnderflowError(r".+")

    def div(self):
        try:
            if self._stack[-1] == 0:
                raise ZeroDivisionError(r".+")
            self._stack[-2] //= self._stack[-1]
            self._stack.pop()
        except IndexError:
            raise StackUnderflowError(r".+")


def evaluate(input_data):
    forth = Forth()
    for data in input_data:
        forth.eval(data)
    return forth.stack()


class StackUnderflowError(Exception):
    pass