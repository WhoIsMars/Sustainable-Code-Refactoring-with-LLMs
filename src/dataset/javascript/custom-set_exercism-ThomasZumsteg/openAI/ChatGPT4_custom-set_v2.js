class CustomSet {
  constructor(items = []) {
    this.items = new Set(items);
  }

  // Tests if item is in a set
  member(item) {
    return this.items.has(item);
  }

  // Number of elements in the set
  size() {
    return this.items.size;
  }

  // Makes a list from a set
  toList() {
    return Array.from(this.items);
  }

  put(item) {
    // Insert an item into a set
    this.items.add(item);
    return this;
  }

  eql(set_b) {
    // Compares two sets for equality
    if (this.size() !== set_b.size()) return false;
    for (const item of this.items) {
      if (!set_b.member(item)) return false;
    }
    return true;
  }

  delete(item) {
    // Removes an item from a set
    this.items.delete(item);
    return this;
  }

  difference(set_b) {
    // Items in one set and not in another
    return new CustomSet([...this.items].filter(item => !set_b.member(item)));
  }

  disjoint(set_b) {
    // Tests if there are no elements in common
    for (const item of this.items) {
      if (set_b.member(item)) return false;
    }
    return true;
  }

  empty() {
    // Remove all items from the set
    this.items.clear();
    return this;
  }

  intersection(set_b) {
    // Items in both sets
    return new CustomSet([...this.items].filter(item => set_b.member(item)));
  }

  subset(set_b) {
    // All elements of one set are contained in this set
    for (const item of set_b.items) {
      if (!this.member(item)) return false;
    }
    return true;
  }

  union(set_b) {
    // Set containing elements from either set
    return new CustomSet([...this.items, ...set_b.items]);
  }
}

module.exports = CustomSet;