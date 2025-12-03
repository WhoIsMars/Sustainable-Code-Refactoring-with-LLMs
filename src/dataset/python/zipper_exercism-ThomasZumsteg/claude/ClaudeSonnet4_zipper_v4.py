class Zipper:
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
        return Zipper({
            'left': self.tree['left'],
            'right': self.tree['right'],
            'value': value
        }, self.crumbs)

    def left(self):
        left_tree = self.tree['left']
        if left_tree:
            return Zipper(left_tree, self.crumbs + (('left', self.tree['value'], self.tree['right']),))

    def set_left(self, left):
        return Zipper({
            'left': left,
            'right': self.tree['right'],
            'value': self.tree['value']
        }, self.crumbs)

    def right(self):
        right_tree = self.tree['right']
        if right_tree:
            return Zipper(right_tree, self.crumbs + (('right', self.tree['value'], self.tree['left']),))

    def set_right(self, right):
        return Zipper({
            'left': self.tree['left'],
            'right': right,
            'value': self.tree['value']
        }, self.crumbs)

    def up(self):
        if not self.crumbs:
            return None
        direction, value, tree = self.crumbs[-1]
        other_direction = 'right' if direction == 'left' else 'left'
        return Zipper({
            'value': value,
            direction: self.tree,
            other_direction: tree
        }, self.crumbs[:-1])

    def to_tree(self):
        current = self
        while current.crumbs:
            current = current.up()
        return current.tree