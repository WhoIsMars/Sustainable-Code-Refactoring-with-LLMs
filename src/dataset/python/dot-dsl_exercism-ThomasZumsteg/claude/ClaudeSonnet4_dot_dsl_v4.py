import functools

NODE, EDGE, ATTR = range(3)


class Node:
    __slots__ = ('name', 'attrs')
    
    def __init__(self, name, attrs=None):
        self.name = name
        self.attrs = attrs or {}

    def __eq__(self, other):
        if not isinstance(other, Node):
            return False
        return self.name == other.name and self.attrs == other.attrs

    def __hash__(self):
        return hash((self.name, tuple(sorted(self.attrs.items()))))


class Edge:
    __slots__ = ('src', 'dst', 'attrs')
    
    def __init__(self, src, dst, attrs=None):
        self.src = src
        self.dst = dst
        self.attrs = attrs or {}

    def __eq__(self, other):
        if not isinstance(other, Edge):
            return False
        return (self.src == other.src and
                self.dst == other.dst and
                self.attrs == other.attrs)

    def __hash__(self):
        return hash((self.src, self.dst, tuple(sorted(self.attrs.items()))))


class Graph:
    __slots__ = ('nodes', 'edges', 'attrs', '_constructors')
    
    def __init__(self, data=None):
        self.nodes = []
        self.edges = []
        self.attrs = {}
        self._constructors = {
            NODE: self._add_node,
            EDGE: self._add_edge,
            ATTR: self._add_attr,
        }

        if data:
            for datum in data:
                if not isinstance(datum, tuple) or len(datum) < 1:
                    raise TypeError(f"Not a valid entry: {datum}")
                elif datum[0] not in self._constructors:
                    raise ValueError("Not a known type")
                
                self._constructors[datum[0]](*datum[1:])

    def _add_node(self, name, attrs):
        self.nodes.append(Node(name, attrs))

    def _add_edge(self, src, dst, attrs):
        self.edges.append(Edge(src, dst, attrs))

    def _add_attr(self, *args):
        if len(args) != 2:
            raise TypeError(f"(ATTR, key, val) Expected 2 args, got {len(args)}: {args}")
        self.attrs[args[0]] = args[1]