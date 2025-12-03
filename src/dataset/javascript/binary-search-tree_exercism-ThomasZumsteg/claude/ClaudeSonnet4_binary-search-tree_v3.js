class BinaryTree {
	constructor(data) {
		this.data = data;
		this.left = null;
		this.right = null;
	}

	insert(data) {
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
	}

	each(func) {
		this.left?.each(func);
		func(this.data);
		this.right?.each(func);
	}
}

module.exports = BinaryTree;