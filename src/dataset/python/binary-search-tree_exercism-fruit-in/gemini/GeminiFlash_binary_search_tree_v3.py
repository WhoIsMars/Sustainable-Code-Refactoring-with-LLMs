class TreeNode:

    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        fmt = 'TreeNode(data={}, left={}, right={})'
        return fmt.format(self.data, self.left, self.right)


class BinarySearchTree:

    def __init__(self, tree_data):
        self.root = None
        for data in tree_data:
            self.insert(data)

    def insert(self, data):
        if self.root is None:
            self.root = TreeNode(data)
            return

        current = self.root
        while True:
            if data <= current.data:
                if current.left is None:
                    current.left = TreeNode(data)
                    return
                else:
                    current = current.left
            else:
                if current.right is None:
                    current.right = TreeNode(data)
                    return
                else:
                    current = current.right

    def data(self):
        return self.root

    def sorted_data(self):
        result = []
        self._inorder_traversal(self.root, result)
        return result

    def _inorder_traversal(self, node, result):
        if node:
            self._inorder_traversal(node.left, result)
            result.append(node.data)
            self._inorder_traversal(node.right, result)