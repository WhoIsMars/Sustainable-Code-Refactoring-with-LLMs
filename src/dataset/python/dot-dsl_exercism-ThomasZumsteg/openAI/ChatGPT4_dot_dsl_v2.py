NODE, EDGE, ATTR = range(3)


class Node:
    __slots__ = ('name', 'attrs')

    def __init__(self, name, attrs=None):
        self.name = name
        self.attrs = attrs or {}

    def __eq__(self, other):
        return self.name == other.name and self.attrs == other.attrs


class Edge:
    __slots__ = ('src', 'dst', 'attrs')

    def __init__(self, src, dst, attrs=None):
        self.src = src
        self.dst = dst
        self.attrs = attrs or {}

    def __eq__(self, other):
        return self.src == other.src and self.dst == other.dst and self.attrs == other.attrs


class Graph:
    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}
        if data:
            self._process_data(data)

    def _process_data(self, data):
        constructors = {
            NODE: self._add_node,
            EDGE: self._add_edge,
            ATTR: self._add_attr,
        }

        for datum in data:
            if not isinstance(datum, tuple) or len(datum) < 1:
                raise TypeError(f"Not a valid entry: {datum}")
            constructor = constructors.get(datum[0])
            if not constructor:
                raise ValueError("Not a known type")
            constructor(*datum[1:])

    def _add_node(self, name, attrs=None):
        self.nodes.append(Node(name, attrs or {}))

    def _add_edge(self, src, dst, attrs=None):
        self.edges.append(Edge(src, dst, attrs or {}))

    def _add_attr(self, key, val):
        if not isinstance(key, str):
            raise TypeError("Key must be a string")
        self.attrs[key] = val