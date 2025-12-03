from collections import defaultdict

class Record():
    def __init__(self, record_id, parent_id):
        self.record_id = record_id
        self.parent_id = parent_id


class Node():
    def __init__(self, node_id):
        self.node_id = node_id
        self.children = []


def BuildTree(records):
    nodes = {}
    if not records:
        return None

    root_found = False
    max_id = -1

    for record in records:
        if (record.record_id == record.parent_id != 0) or record.record_id < record.parent_id:
            raise ValueError("Invalid record {}".format(record))

        max_id = max(max_id, record.record_id)

    if max_id == -1:
        return None

    if max_id != len(records) - 1:
        raise ValueError("To many nodes")

    parents = defaultdict(list)
    for record in records:
        node = Node(record.record_id)
        nodes[record.record_id] = node

        if record.record_id == 0:
            root_found = True

        if record.record_id != 0:
            parents[record.parent_id].append(node)

    if not root_found:
        raise ValueError("No root node")

    for node_id, node in nodes.items():
        node.children = sorted(parents[node_id], key=lambda n: n.node_id)

    return nodes[0]