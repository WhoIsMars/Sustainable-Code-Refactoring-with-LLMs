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
    if not records:
        return None
    
    nodes = {}
    children_map = defaultdict(list)
    max_id = 0
    
    for record in records:
        if (record.record_id == record.parent_id != 0) or \
            record.record_id < record.parent_id:
            raise ValueError("Invalid record {}".format(record))
        
        node = Node(record.record_id)
        nodes[record.record_id] = node
        max_id = max(max_id, record.record_id)
        
        if record.record_id != 0:
            children_map[record.parent_id].append(node)
    
    if 0 not in nodes:
        raise ValueError("No root node")
    
    if len(records) - 1 != max_id:
        raise ValueError("To many nodes")
    
    for parent_id, children in children_map.items():
        children.sort(key=lambda n: n.node_id)
        nodes[parent_id].children = children
    
    return nodes[0]