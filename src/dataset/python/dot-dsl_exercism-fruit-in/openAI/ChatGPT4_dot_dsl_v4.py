NODE, EDGE, ATTR = range(3)


class Node:
    __slots__ = ('name', 'attrs')

    def __init__(self, name, attrs):
        self.name = name
        self.attrs = attrs

    def __eq__(self, other):
        return self.name == other.name and self.attrs == other.attrs


class Edge:
    __slots__ = ('src', 'dst', 'attrs')

    def __init__(self, src, dst, attrs):
        self.src = src
        self.dst = dst
        self.attrs = attrs

    def __eq__(self, other):
        return self.src == other.src and self.dst == other.dst and self.attrs == other.attrs


class Graph:
    __slots__ = ('nodes', 'edges', 'attrs')

    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}

        if data is None:
            return

        if not isinstance(data, list):
            raise TypeError(r".+")

        for d in data:
            if not isinstance(d, tuple) or len(d) not in (3, 4):
                raise TypeError(r".+")

            dtype, *args = d
            if dtype == NODE:
                if len(args) != 2 or not isinstance(args[0], str) or not isinstance(args[1], dict):
                    raise ValueError(r".+")
                self.nodes.append(Node(*args))
            elif dtype == EDGE:
                if len(args) != 3 or not all(isinstance(arg, str) for arg in args[:2]) or not isinstance(args[2], dict):
                    raise ValueError(r".+")
                self.edges.append(Edge(*args))
            elif dtype == ATTR:
                if len(args) != 2 or not all(isinstance(arg, str) for arg in args):
                    raise ValueError(r".+")
                self.attrs[args[0]] = args[1]
            else:
                raise ValueError(r".+")