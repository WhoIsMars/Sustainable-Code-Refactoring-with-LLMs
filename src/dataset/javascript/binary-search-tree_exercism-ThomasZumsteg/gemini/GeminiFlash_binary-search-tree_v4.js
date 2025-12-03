var BinaryTree = function(data) {
	this.data = data;
	this.left = null;
	this.right = null;
};

BinaryTree.prototype.insert = function(data) {
	let node = data <= this.data ? 'left' : 'right';
	if (this[node]) {
		this[node].insert(data);
	} else {
		this[node] = new BinaryTree(data);
	}
};

BinaryTree.prototype.each = function(func) {
	if (this.left) {
		this.left.each(func);
	}
	func(this.data);
	if (this.right) {
		this.right.each(func);
	}
};

module.exports = BinaryTree;