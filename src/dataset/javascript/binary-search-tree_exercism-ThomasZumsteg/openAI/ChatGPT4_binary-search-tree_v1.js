class BinaryTree {
  constructor(data) {
    this.data = data;
    this.left = null;
    this.right = null;
  }

  insert(data) {
    const node = data <= this.data ? 'left' : 'right';
    if (!this[node]) {
      this[node] = new BinaryTree(data);
    } else {
      this[node].insert(data);
    }
  }

  each(func) {
    if (this.left) this.left.each(func);
    func(this.data);
    if (this.right) this.right.each(func);
  }
}

module.exports = BinaryTree;