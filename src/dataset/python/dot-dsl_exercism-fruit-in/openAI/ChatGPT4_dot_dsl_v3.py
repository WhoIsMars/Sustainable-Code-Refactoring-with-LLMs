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
    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}

        if data is None:
            return

        if not isinstance(data, list):
            raise TypeError(r".+")

        append_node = self.nodes.append
        append_edge = self.edges.append
        attrs_set = self.attrs.__setitem__

        for d in data:
            if not isinstance(d, tuple) or len(d) not in (3, 4):
                raise TypeError(r".+")

            dtype = d[0]
            if dtype == NODE:
                if len(d) != 3 or not isinstance(d[1], str) or not isinstance(d[2], dict):
                    raise ValueError(r".+")
                append_node(Node(d[1], d[2]))
            elif dtype == EDGE:
                if len(d) != 4 or not isinstance(d[1], str) or not isinstance(d[2], str) or not isinstance(d[3], dict):
                    raise ValueError(r".+")
                append_edge(Edge(d[1], d[2], d[3]))
            elif dtype == ATTR:
                if len(d) != 3 or not isinstance(d[1], str) or not isinstance(d[2], str):
                    raise ValueError(r".+")
                attrs_set(d[1], d[2])
            else:
                raise ValueError(r".+")