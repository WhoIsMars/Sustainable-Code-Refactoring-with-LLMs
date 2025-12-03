var BinaryTree = function(data) {
	this.data = data;
	this.left = null;
	this.right = null;
}

BinaryTree.prototype.insert = function(data) {
	if (data <= this.data) {
		if (this.left) {
			this.left.insert(data);
		} else {
			this.left = new BinaryTree(data);
		}
	} else {
		if (this.right) {
			this.right.insert(data);
		} else {
			this.right = new BinaryTree(data);
		}
	}
};

BinaryTree.prototype.each = function(func) {
	if (this.left) this.left.each(func);
	func(this.data);
	if (this.right) this.right.each(func);
};

module.exports = BinaryTree;