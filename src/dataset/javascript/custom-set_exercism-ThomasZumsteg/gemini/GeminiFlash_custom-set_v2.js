var CustomSet = function(items) {
    this.items = [];
    if (items) {
        for (var i = 0; i < items.length; i++) {
            this.put(items[i]);
        }
    }
};

CustomSet.prototype.member = function(item) {
    return this.items.includes(item);
};

CustomSet.prototype.size = function() {
    return this.items.length;
};

CustomSet.prototype.toList = function() {
    return [...this.items]; // Return a copy to prevent modification of internal state
};

CustomSet.prototype.put = function(item) {
    if (!this.member(item)) {
        this.items.push(item);
        this.items.sort(); // Keep sorted on insertion
    }
    return this;
};

CustomSet.prototype.eql = function(set_b) {
    if (this.items.length !== set_b.items.length) {
        return false;
    }
    for (let i = 0; i < this.items.length; i++) {
        if (this.items[i] !== set_b.items[i]) {
            return false;
        }
    }
    return true;
};

CustomSet.prototype.delete = function(item) {
    const index = this.items.indexOf(item);
    if (index > -1) {
        this.items.splice(index, 1);
    }
    return this;
};

CustomSet.prototype.difference = function(set_b) {
    const result = [];
    for (let i = 0; i < this.items.length; i++) {
        const item = this.items[i];
        if (!set_b.member(item)) {
            result.push(item);
        }
    }
    return new CustomSet(result);
};

CustomSet.prototype.disjoint = function(set_b) {
    if (this.size() === 0 || set_b.size() === 0) {
        return true;
    }

    for (let i = 0; i < this.items.length; i++) {
        if (set_b.member(this.items[i])) {
            return false;
        }
    }

    return true;
};

CustomSet.prototype.empty = function() {
    this.items.length = 0; // More efficient way to clear the array
    return this;
};

CustomSet.prototype.intersection = function(set_b) {
    const result = [];
    for (let i = 0; i < this.items.length; i++) {
        const item = this.items[i];
        if (set_b.member(item)) {
            result.push(item);
        }
    }
    return new CustomSet(result);
};

CustomSet.prototype.subset = function(set_b) {
    for (let i = 0; i < set_b.items.length; i++) {
        if (!this.member(set_b.items[i])) {
            return false;
        }
    }
    return true;
};

CustomSet.prototype.union = function(set_b) {
    const combined = [...this.items];
    for (let i = 0; i < set_b.items.length; i++) {
        const item = set_b.items[i];
        if (!this.member(item)) {
            combined.push(item);
        }
    }
    return new CustomSet(combined);
};

module.exports = CustomSet;