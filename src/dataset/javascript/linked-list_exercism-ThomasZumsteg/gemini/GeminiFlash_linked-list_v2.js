var LinkedList = function() {
	this.head = null;
	this.tail = null;
	this.length = 0;
};

LinkedList.prototype.push = function(val) {
	const newElement = { val: val, next: null, prev: this.tail };

	if (this.tail) {
		this.tail.next = newElement;
	} else {
		this.head = newElement;
	}

	this.tail = newElement;
	this.length++;
};

LinkedList.prototype.pop = function() {
	if (!this.head) {
		return undefined;
	}

	const element = this.tail;
	if (this.length === 1) {
		this.head = null;
		this.tail = null;
	} else {
		this.tail = element.prev;
		this.tail.next = null;
	}

	this.length--;
	return element.val;
};

LinkedList.prototype.unshift = function(val) {
	const newElement = { val: val, next: this.head, prev: null };

	if (this.head) {
		this.head.prev = newElement;
	} else {
		this.tail = newElement;
	}

	this.head = newElement;
	this.length++;
};

LinkedList.prototype.shift = function() {
	if (!this.head) {
		return undefined;
	}

	const element = this.head;
	if (this.length === 1) {
		this.head = null;
		this.tail = null;
	} else {
		this.head = element.next;
		this.head.prev = null;
	}

	this.length--;
	return element.val;
};

LinkedList.prototype.count = function() {
	return this.length;
};

LinkedList.prototype.delete = function(val) {
	let current = this.head;

	while (current) {
		if (current.val === val) {
			if (current.prev) {
				current.prev.next = current.next;
			} else {
				this.head = current.next;
			}

			if (current.next) {
				current.next.prev = current.prev;
			} else {
				this.tail = current.prev;
			}

			this.length--;
			return;
		}
		current = current.next;
	}
};

module.exports = LinkedList;