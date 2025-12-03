var BinaryTree = function(data) {
	this.data = data;
	this.left = null;
	this.right = null;
}

BinaryTree.prototype.insert = function(data) {
	var current = this;
	while (true) {
		if (data <= current.data) {
			if (current.left) {
				current = current.left;
			} else {
				current.left = new BinaryTree(data);
				break;
			}
		} else {
			if (current.right) {
				current = current.right;
			} else {
				current.right = new BinaryTree(data);
				break;
			}
		}
	}
};

BinaryTree.prototype.each = function(func) {
	var stack = [];
	var current = this;
	
	while (current || stack.length > 0) {
		while (current) {
			stack.push(current);
			current = current.left;
		}
		current = stack.pop();
		func(current.data);
		current = current.right;
	}
};

module.exports = BinaryTree;