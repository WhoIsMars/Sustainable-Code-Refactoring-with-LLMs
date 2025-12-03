from collections import defaultdict

class Record():
    __slots__ = ['record_id', 'parent_id']  # Reduce memory footprint
    def __init__(self, record_id, parent_id):
        self.record_id = record_id
        self.parent_id = parent_id


class Node():
    __slots__ = ['node_id', 'children'] # Reduce memory footprint
    def __init__(self, node_id):
        self.node_id = node_id
        self.children = []


def BuildTree(records):
    nodes = {}
    parents = defaultdict(list)
    max_id = -1  # Initialize to -1 to handle empty records case correctly
    root_found = False
    record_count = 0

    for record in records:
        record_id = record.record_id
        parent_id = record.parent_id

        if (record_id == parent_id != 0) or record_id < parent_id:
            raise ValueError(f"Invalid record {record_id}")

        node = Node(record_id)
        nodes[record_id] = node
        max_id = max(max_id, record_id)

        if record_id != 0:
            parents[parent_id].append(node)
        else:
            root_found = True

        record_count += 1

    if not nodes:
        return None

    if 0 not in nodes:
        raise ValueError("No root node")

    if record_count -1 != max_id:
        raise ValueError("To many nodes")

    for parent_id, children in parents.items():
        children.sort(key=lambda n: n.node_id)

    for node_id, node in nodes.items():
        node.children = parents[node_id]

    return nodes[0]