class Zipper(object):
    __slots__ = ('tree', 'crumbs')

    @staticmethod
    def from_tree(tree):
        return Zipper(tree, ())

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
            crumbs = self.crumbs + (('left', self.tree['value'], self.tree.get('right')),)
            return Zipper(left_tree, crumbs)
        return None

    def set_left(self, left):
        new_tree = self.tree.copy()
        new_tree['left'] = left
        return Zipper(new_tree, self.crumbs)

    def right(self):
        right_tree = self.tree.get('right')
        if right_tree:
            crumbs = self.crumbs + (('right', self.tree['value'], self.tree.get('left')),)
            return Zipper(right_tree, crumbs)
        return None

    def set_right(self, right):
        new_tree = self.tree.copy()
        new_tree['right'] = right
        return Zipper(new_tree, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None

        direction, value, sibling = self.crumbs[-1]
        new_tree = {'value': value, direction: self.tree}

        if direction == 'right':
            new_tree['left'] = sibling
        else:
            new_tree['right'] = sibling

        return Zipper(new_tree, self.crumbs[:-1])

    def to_tree(self):
        zipper = self
        while True:
            up_zipper = zipper.up()
            if up_zipper is None:
                return zipper.tree
            zipper = up_zipper