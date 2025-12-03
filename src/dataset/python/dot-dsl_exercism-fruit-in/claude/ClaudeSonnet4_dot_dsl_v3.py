NODE, EDGE, ATTR = range(3)


class Node:
    __slots__ = ('name', 'attrs')
    
    def __init__(self, name, attrs):
        self.name = name
        self.attrs = attrs

    def __eq__(self, other):
        if not isinstance(other, Node):
            return False
        return self.name == other.name and self.attrs == other.attrs

    def __hash__(self):
        return hash((self.name, tuple(sorted(self.attrs.items()))))


class Edge:
    __slots__ = ('src', 'dst', 'attrs')
    
    def __init__(self, src, dst, attrs):
        self.src = src
        self.dst = dst
        self.attrs = attrs

    def __eq__(self, other):
        if not isinstance(other, Edge):
            return False
        return (self.src == other.src and
                self.dst == other.dst and
                self.attrs == other.attrs)

    def __hash__(self):
        return hash((self.src, self.dst, tuple(sorted(self.attrs.items()))))


class Graph:
    __slots__ = ('nodes', 'edges', 'attrs')
    
    def __init__(self, data=[]):
        self.nodes = []
        self.edges = []
        self.attrs = {}

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
                if (len(d) != 4 or not isinstance(d[1], str) or 
                    not isinstance(d[2], str) or not isinstance(d[3], dict)):
                    raise ValueError(r".+")
                self.edges.append(Edge(d[1], d[2], d[3]))
                
            elif d_type == ATTR:
                if len(d) != 3 or not isinstance(d[1], str) or not isinstance(d[2], str):
                    raise ValueError(r".+")
                self.attrs[d[1]] = d[2]
                
            else:
                raise ValueError(r".+")