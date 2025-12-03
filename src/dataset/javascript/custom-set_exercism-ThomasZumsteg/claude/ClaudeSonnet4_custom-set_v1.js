var CustomSet = function(items) {
	/* A set object */
	this.items = [];
	this._itemSet = new Set();
	
	if (items) {
		for(var i = 0; i < items.length; i++) {
			if (!this._itemSet.has(items[i])) {
				this.items.push(items[i]);
				this._itemSet.add(items[i]);
			}
		}
		this.items.sort();
	}
};

// Tests if item is in a set
CustomSet.prototype.member = function(item) { 
	return this._itemSet.has(item);
};

// Number of elements in the set
CustomSet.prototype.size = function() { 
	return this.items.length;
};

// Makes a list from a set
CustomSet.prototype.toList = function() { 
	return this.items.slice();
};

CustomSet.prototype.put = function(item) {
	/* Insert an item into a set */
	if(!this._itemSet.has(item)) {
		this.items.push(item);
		this._itemSet.add(item);
		this.items.sort();
	}
	return this;
};

CustomSet.prototype.eql = function(set_b) {
	/* Compares two sets for equality */
	if(this.items.length !== set_b.items.length)
		return false;
	for(var i = 0; i < this.items.length; i++) {
		if(this.items[i] !== set_b.items[i])
			return false;
	}
	return true;
};

CustomSet.prototype.delete = function(item) {
	/* Removes an item from a set */
	if (this._itemSet.has(item)) {
		var index = this.items.indexOf(item);
		this.items.splice(index, 1);
		this._itemSet.delete(item);
	}
	return this;
};

CustomSet.prototype.difference = function(set_b) {
	/* Items in one set and not in another */
	var result = [];
	for(var i = 0; i < this.items.length; i++) {
		if (!set_b._itemSet.has(this.items[i])) {
			result.push(this.items[i]);
		}
	}
	return new CustomSet(result);
};

CustomSet.prototype.disjoint = function(set_b) {
	/* Tests if there are no elements in common */
	if(this.items.length === 0 || set_b.items.length === 0)
		return true;
	
	var smaller = this.items.length <= set_b.items.length ? this : set_b;
	var larger = smaller === this ? set_b : this;
	
	for(var i = 0; i < smaller.items.length; i++) {
		if (larger._itemSet.has(smaller.items[i])) {
			return false;
		}
	}
	return true;
};

CustomSet.prototype.empty = function() {
	/* Remove all items from the set */
	this.items = [];
	this._itemSet.clear();
	return this;
};

CustomSet.prototype.intersection = function(set_b) {
	/* Items in both sets */
	var result = [];
	for(var i = 0; i < this.items.length; i++) {
		if (set_b._itemSet.has(this.items[i])) {
			result.push(this.items[i]);
		}
	}
	return new CustomSet(result);
};

CustomSet.prototype.subset = function(set_b) {
	/* All elements of one set are contained in this set */
	for(var i = 0; i < set_b.items.length; i++) {
		if (!this._itemSet.has(set_b.items[i])) {
			return false;
		}
	}
	return true;
};

CustomSet.prototype.union = function(set_b) {
	/* Set containing elements from either set */
	var result = this.items.slice();
	for(var i = 0; i < set_b.items.length; i++) {
		if (!this._itemSet.has(set_b.items[i])) {
			result.push(set_b.items[i]);
		}
	}
	return new CustomSet(result);
};

module.exports = CustomSet;