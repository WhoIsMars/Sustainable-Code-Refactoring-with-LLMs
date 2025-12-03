class Node{
  constructor(value){
    this.value = value;
    this.previous = null;
    this.next = null;
  }
}

export default class LinkedList{
  constructor(){
    this.head = null;
    this.tail = null;
    this.length = 0;
  }

  push(value){
    const node = new Node(value);

    if(this.length === 0){
      this.head = this.tail = node;
    } else{
      this.tail.next = node;
      node.previous = this.tail;
      this.tail = node;
    }
    this.length++;
  }

  pop(){
    if(this.length === 0) return null;

    const oldTailValue = this.tail.value;

    if(this.length === 1){
      this.head = this.tail = null;
    } else{
      this.tail = this.tail.previous;
      this.tail.next = null;
    }
    this.length--;
    return oldTailValue;
  }

  shift(){
    if(this.length === 0) return null;

    const oldHeadValue = this.head.value;

    if(this.length === 1){
      this.head = this.tail = null;
    } else{
      this.head = this.head.next;
      this.head.previous = null;
    }
    this.length--;
    return oldHeadValue;
  }

  unshift(value){
    const node = new Node(value);

    if(this.length === 0){
      this.head = this.tail = node;
    } else{
      node.next = this.head;
      this.head.previous = node;
      this.head = node;
    }
    this.length++;
  }

  delete(value){
    if(this.length === 0) return;

    if(this.head.value === value){
      this.shift();
      return;
    }
    
    if(this.tail.value === value){
      this.pop();
      return;
    }

    let currentNode = this.head.next;
    while(currentNode && currentNode !== this.tail){
      if(currentNode.value === value){
        currentNode.previous.next = currentNode.next;
        currentNode.next.previous = currentNode.previous;
        this.length--;
        return;
      }
      currentNode = currentNode.next;
    }
  }

  count(){
    return this.length;
  }
}