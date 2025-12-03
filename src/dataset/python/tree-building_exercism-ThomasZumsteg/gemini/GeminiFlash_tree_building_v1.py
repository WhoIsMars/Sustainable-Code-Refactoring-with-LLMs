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

    root_exists = False
    max_id = -1

    for record in records:
        if record.record_id == 0:
            root_exists = True
        max_id = max(max_id, record.record_id)

    if not root_exists:
        raise ValueError("No root node")

    if len(records) != max_id + 1:
        raise ValueError("To many nodes")
    
    records_dict = {record.record_id: record for record in records}

    for record_id in range(max_id + 1):
        if record_id not in records_dict:
            raise ValueError("Missing node")

    for record in records:
        if (record.record_id == record.parent_id != 0) or record.record_id < record.parent_id:
            raise ValueError("Invalid record")

    nodes = {record.record_id: Node(record.record_id) for record in records}

    root = nodes[0]
    
    for node_id in nodes:
        if node_id != 0:
            parent_id = records_dict[node_id].parent_id
            parent_node = nodes[parent_id]
            parent_node.children.append(nodes[node_id])
    
    for node in nodes.values():
        node.children.sort(key=lambda n: n.node_id)

    return root