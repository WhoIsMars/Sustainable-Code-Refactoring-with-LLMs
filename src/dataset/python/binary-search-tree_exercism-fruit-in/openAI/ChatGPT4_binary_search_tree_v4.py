class TreeNode:

    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return f'TreeNode(data={self.data}, left={self.left}, right={self.right})'


class BinarySearchTree:

    def __init__(self, tree_data):
        self.root = None
        for data in tree_data:
            self.insert(data)

    def insert(self, data):
        def _insert(node, data):
            if node is None:
                return TreeNode(data)
            if data <= node.data:
                node.left = _insert(node.left, data)
            else:
                node.right = _insert(node.right, data)
            return node

        self.root = _insert(self.root, data)

    def data(self):
        return self.root

    def sorted_data(self):
        def _in_order_traversal(node):
            if node is None:
                return []
            return _in_order_traversal(node.left) + [node.data] + _in_order_traversal(node.right)

        return _in_order_traversal(self.root)