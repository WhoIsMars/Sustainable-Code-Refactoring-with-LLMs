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
    parent_children = defaultdict(list)
    max_id = 0
    
    for record in records:
        record_id = record.record_id
        parent_id = record.parent_id
        
        if (record_id == parent_id != 0) or record_id < parent_id:
            raise ValueError("Invalid record {}".format(record))
        
        if record_id in nodes:
            raise ValueError("Duplicate record id")
            
        node = Node(record_id)
        nodes[record_id] = node
        
        if record_id > max_id:
            max_id = record_id
        
        if record_id != 0:
            parent_children[parent_id].append(node)
    
    if 0 not in nodes:
        raise ValueError("No root node")
    
    if len(records) - 1 != max_id:
        raise ValueError("To many nodes")
    
    # Assign children and sort once
    for parent_id, children in parent_children.items():
        children.sort(key=lambda n: n.node_id)
        nodes[parent_id].children = children
    
    return nodes[0]