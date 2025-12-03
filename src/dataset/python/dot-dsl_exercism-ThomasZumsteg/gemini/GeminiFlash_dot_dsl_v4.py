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


class Graph(object):
    __slots__ = ('nodes', 'edges', 'attrs')

    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}

        if data:
            constructors = {
                NODE: self._add_node,
                EDGE: self._add_edge,
                ATTR: self._add_attr,
            }

            for datum in data:
                if not isinstance(datum, tuple) or len(datum) < 1:
                    raise TypeError("Not a valid entry: {}".format(datum))
                type_code = datum[0]
                if type_code not in constructors:
                    raise ValueError("Not a known type")

                constructors[type_code](*datum[1:])

    def _add_node(self, name, attrs):
        self.nodes.append(Node(name, attrs=attrs))

    def _add_edge(self, src, dst, attrs):
        self.edges.append(Edge(src, dst, attrs=attrs))

    def _add_attr(self, key, val):
        self.attrs[key] = val