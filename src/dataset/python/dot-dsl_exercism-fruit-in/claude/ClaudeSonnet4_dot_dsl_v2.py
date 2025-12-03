NODE, EDGE, ATTR = 0, 1, 2


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
        return (self.src == other.src and
                self.dst == other.dst and
                self.attrs == other.attrs)


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

            d_type = d[0]
            if d_type == NODE:
                if len(d) != 3 or not isinstance(d[1], str) or not isinstance(d[2], dict):
                    raise ValueError(r".+")
                self.nodes.append(Node(d[1], d[2]))
            elif d_type == EDGE:
                if len(d) != 4 or not isinstance(d[1], str) or \
                        not isinstance(d[2], str) or not isinstance(d[3], dict):
                    raise ValueError(r".+")
                self.edges.append(Edge(d[1], d[2], d[3]))
            elif d_type == ATTR:
                if len(d) != 3 or not isinstance(d[1], str) or not isinstance(d[2], str):
                    raise ValueError(r".+")
                self.attrs[d[1]] = d[2]
            else:
                raise ValueError(r".+")