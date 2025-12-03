class Forth:

    def __init__(self):
        self._stack = []
        self._definitions = {}
        self._builtin_ops = {
            "+": self.add,
            "-": self.sub,
            "*": self.mul,
            "/": self.div,
            "dup": self.dup,
            "drop": self.drop,
            "swap": self.swap,
            "over": self.over
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
            elif op in self._builtin_ops:
                self._builtin_ops[op]()
            elif op == ":":
                i = self._handle_definition(ops, i)
            else:
                self._stack.append(int(op))
            i += 1

    def _handle_definition(self, ops, start_idx):
        end_idx = start_idx + 1
        while end_idx < len(ops) and ops[end_idx] != ";":
            if ops[end_idx] == ":":
                break
            end_idx += 1
        
        if end_idx >= len(ops) or ops[end_idx] != ";" or end_idx - start_idx < 3:
            raise ValueError(r".+")
        
        name = ops[start_idx + 1]
        try:
            int(name)
            raise ValueError(r".+")
        except ValueError:
            if name.isdigit() or (name.startswith('-') and name[1:].isdigit()):
                raise ValueError(r".+")
        
        definition_ops = ops[start_idx + 2:end_idx]
        self.define([name] + definition_ops)
        return end_idx

    def define(self, ops):
        expanded_ops = []
        for op in ops[1:]:
            if op in self._definitions:
                expanded_ops.append(self._definitions[op])
            elif op not in self._builtin_ops:
                int(op)
                expanded_ops.append(op)
            else:
                expanded_ops.append(op)
        self._definitions[ops[0]] = " ".join(expanded_ops)

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
        b = self._stack.pop()
        self._stack[-1] += b

    def sub(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        b = self._stack.pop()
        self._stack[-1] -= b

    def mul(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        b = self._stack.pop()
        self._stack[-1] *= b

    def div(self):
        if len(self._stack) < 2:
            raise StackUnderflowError(r".+")
        b = self._stack.pop()
        if b == 0:
            raise ZeroDivisionError(r".+")
        self._stack[-1] //= b

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