class Zipper(object):
    __slots__ = ('tree', 'crumbs')

    @staticmethod
    def from_tree(tree):
        return Zipper(tree, [])

    def __init__(self, tree, crumbs):
        self.tree = tree
        self.crumbs = crumbs

    def value(self):
        return self.tree['value']

    def set_value(self, value):
        new_tree = self.tree.copy()
        new_tree['value'] = value
        return Zipper(new_tree, self.crumbs)

    def left(self):
        left_tree = self.tree.get('left')
        if left_tree:
            crumbs = self.crumbs[:]
            crumbs.append(('left', self.tree['value'], self.tree.get('right')))
            return Zipper(left_tree, crumbs)
        return None

    def set_left(self, left):
        new_tree = self.tree.copy()
        new_tree['left'] = left
        return Zipper(new_tree, self.crumbs)

    def right(self):
        right_tree = self.tree.get('right')
        if right_tree:
            crumbs = self.crumbs[:]
            crumbs.append(('right', self.tree['value'], self.tree.get('left')))
            return Zipper(right_tree, crumbs)
        return None

    def set_right(self, right):
        new_tree = self.tree.copy()
        new_tree['right'] = right
        return Zipper(new_tree, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None

        direction, value, other_tree = self.crumbs[-1]
        crumbs = self.crumbs[:-1]

        new_tree = {'value': value}
        new_tree[direction] = self.tree
        new_tree['left' if direction == 'right' else 'right'] = other_tree

        return Zipper(new_tree, crumbs)

    def to_tree(self):
        current = self
        while True:
            up = current.up()
            if up is None:
                return current.tree
            current = up