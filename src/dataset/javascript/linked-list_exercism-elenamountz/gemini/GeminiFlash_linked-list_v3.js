class Node {
  constructor(value) {
    this.value = value;
    this.previous = null;
    this.next = null;
  }
}

export default class LinkedList {
  constructor() {
    this.head = null;
    this.tail = null;
    this.length = 0;
  }

  push(value) {
    const node = new Node(value);

    if (!this.head) {
      this.head = node;
      this.tail = node;
    } else {
      this.tail.next = node;
      node.previous = this.tail;
      this.tail = node;
    }
    this.length++;
  }

  pop() {
    if (!this.head) return null;

    const oldTailValue = this.tail.value;
    this.tail = this.tail.previous;

    if (this.tail) {
      this.tail.next = null;
    } else {
      this.head = null;
    }

    this.length--;
    return oldTailValue;
  }

  shift() {
    if (!this.head) return null;

    const oldHeadValue = this.head.value;
    this.head = this.head.next;

    if (this.head) {
      this.head.previous = null;
    } else {
      this.tail = null;
    }

    this.length--;
    return oldHeadValue;
  }

  unshift(value) {
    const node = new Node(value);

    if (!this.head) {
      this.head = node;
      this.tail = node;
    } else {
      this.head.previous = node;
      node.next = this.head;
      this.head = node;
    }
    this.length++;
  }

  delete(value) {
    if (!this.head) return;

    if (this.head.value === value) {
      this.shift();
      return;
    }

    if (this.tail.value === value) {
      this.pop();
      return;
    }

    let currentNode = this.head.next;
    while (currentNode) {
      if (currentNode.value === value) {
        currentNode.previous.next = currentNode.next;
        if (currentNode.next) {
          currentNode.next.previous = currentNode.previous;
        }
        this.length--;
        return;
      }
      currentNode = currentNode.next;
    }
  }

  count() {
    return this.length;
  }
}