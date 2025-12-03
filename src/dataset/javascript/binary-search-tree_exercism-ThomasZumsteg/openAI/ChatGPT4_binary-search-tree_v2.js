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
        const stack = [];
        let current = this;

        while (stack.length > 0 || current) {
            while (current) {
                stack.push(current);
                current = current.left;
            }
            current = stack.pop();
            func(current.data);
            current = current.right;
        }
    }
}

module.exports = BinaryTree;