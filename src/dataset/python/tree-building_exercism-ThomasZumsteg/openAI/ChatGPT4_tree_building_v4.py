from collections import defaultdict

class Record:
    __slots__ = ('record_id', 'parent_id')
    def __init__(self, record_id, parent_id):
        self.record_id = record_id
        self.parent_id = parent_id


class Node:
    __slots__ = ('node_id', 'children')
    def __init__(self, node_id):
        self.node_id = node_id
        self.children = []


def BuildTree(records):
    if not records:
        return None

    nodes = {}
    parents = defaultdict(list)
    max_id = -1

    for record in records:
        if record.record_id == record.parent_id != 0 or record.record_id < record.parent_id:
            raise ValueError(f"Invalid record {record}")
        node = nodes.setdefault(record.record_id, Node(record.record_id))
        max_id = max(max_id, record.record_id)
        if record.record_id != 0:
            parents[record.parent_id].append(node)

    for parent_id, children in parents.items():
        if parent_id not in nodes:
            raise ValueError("No root node")
        nodes[parent_id].children.extend(sorted(children, key=lambda n: n.node_id))

    if 0 not in nodes or len(nodes) - 1 != max_id:
        raise ValueError("Invalid tree structure")

    return nodes[0]