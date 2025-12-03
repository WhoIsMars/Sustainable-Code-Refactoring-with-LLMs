from collections import defaultdict

class Record:
    def __init__(self, record_id, parent_id):
        self.record_id = record_id
        self.parent_id = parent_id


class Node:
    def __init__(self, node_id):
        self.node_id = node_id
        self.children = []


def BuildTree(records):
    if not records:
        return None

    nodes = {}
    children_map = defaultdict(list)

    for record in records:
        if record.record_id < record.parent_id or (record.record_id == record.parent_id != 0):
            raise ValueError(f"Invalid record {record}")
        nodes[record.record_id] = Node(record.record_id)
        children_map[record.parent_id].append(record.record_id)

    if 0 not in nodes:
        raise ValueError("No root node")

    for parent_id, child_ids in children_map.items():
        if parent_id in nodes:
            nodes[parent_id].children.extend(nodes[child_id] for child_id in sorted(child_ids))

    if len(nodes) - 1 != max(nodes.keys()):
        raise ValueError("Too many nodes")

    return nodes[0]