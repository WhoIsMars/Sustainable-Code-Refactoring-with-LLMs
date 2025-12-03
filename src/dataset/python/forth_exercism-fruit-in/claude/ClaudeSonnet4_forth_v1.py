class Forth:

    def __init__(self):
        self._stack = []
        self._definitions = {}

    def stack(self):
        return self._stack

    def eval(self, data):
        ops = data.lower().split()
        i = 0
        
        while i < len(ops):
            op = ops[i]

            if op in self._definitions:
                self.eval(self._definitions[op])
            elif op == "+":
                self.add()
            elif op == "-":
                self.sub()
            elif op == "*":
                self.mul()
            elif op == "/":
                self.div()
            elif op == "dup":
                self.dup()
            elif op == "drop":
                self.drop()
            elif op == "swap":
                self.swap()
            elif op == "over":
                self.over()
            elif op == ":":
                j = i + 1
                while j < len(ops) and ops[j] != ";":
                    j += 1
                
                if j >= len(ops) or j - i < 3:
                    raise ValueError(r".+")
                
                ops_ = ops[i+1:j]
                
                try:
                    int(ops_[0])
                    raise ValueError(r".+")
                except ValueError:
                    if ops_[0].isdigit() or (ops_[0].startswith('-') and ops_[0][1:].isdigit()):
                        raise ValueError(r".+")

                self.define(ops_)
                i = j
            else:
                self._stack.append(int(op))
            
            i += 1

    def define(self, ops):
        definition_parts = []
        for i in range(1, len(ops)):
            if ops[i] in self._definitions:
                definition_parts.append(self._definitions[ops[i]])
            elif ops[i] not in ["+", "-", "*", "/", "dup", "drop", "swap", "over"]:
                int(ops[i])
                definition_parts.append(ops[i])
            else:
                definition_parts.append(ops[i])
        self._definitions[ops[0]] = " ".join(definition_parts)

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
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        x = self._stack.pop()
        self._stack[-1] += x

    def sub(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        x = self._stack.pop()
        self._stack[-1] -= x

    def mul(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        x = self._stack.pop()
        self._stack[-1] *= x

    def div(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        x = self._stack.pop()
        if x == 0:
            raise ZeroDivisionError(r".+")
        self._stack[-1] //= x

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