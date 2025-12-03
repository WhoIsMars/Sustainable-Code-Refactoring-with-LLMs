import functools

NODE, EDGE, ATTR = range(3)


class Node(object):
    __slots__ = ('name', 'attrs')

    def __init__(self, name, attrs=None):
        self.name = name
        self.attrs = attrs if attrs is not None else {}

    def __eq__(self, other):
        if not isinstance(other, Node):
            return False
        return self.name == other.name and self.attrs == other.attrs

    def __hash__(self):
        return hash((self.name, tuple(sorted(self.attrs.items()))))


class Edge(object):
    __slots__ = ('src', 'dst', 'attrs')

    def __init__(self, src, dst, attrs=None):
        self.src = src
        self.dst = dst
        self.attrs = attrs if attrs is not None else {}

    def __eq__(self, other):
        if not isinstance(other, Edge):
            return False
        return (self.src == other.src and
                self.dst == other.dst and
                self.attrs == other.attrs)

    def __hash__(self):
        return hash((self.src, self.dst, tuple(sorted(self.attrs.items()))))


class Graph(object):
    __slots__ = ('nodes', 'edges', 'attrs')

    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}
        constructors = {
            NODE: self._add_node,
            EDGE: self._add_edge,
            ATTR: self._add_attr,
        }

        if data:
            for datum in data:
                if not isinstance(datum, tuple) or len(datum) < 1:
                    raise TypeError("Not a valid entry: {}".format(datum))
                entry_type = datum[0]
                if entry_type not in constructors:
                    raise ValueError("Not a known type")

                constructors[entry_type](*datum[1:])

    def _add_node(self, name, attrs):
        self.nodes.append(Node(name, attrs))

    def _add_edge(self, src, dst, attrs):
        self.edges.append(Edge(src, dst, attrs))

    def _add_attr(self, key, val):
        self.attrs[key] = val