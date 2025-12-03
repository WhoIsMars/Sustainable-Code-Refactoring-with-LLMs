export default class BinarySearchTree {
  public readonly data: number;
  public left: BinarySearchTree | null = null;
  public right: BinarySearchTree | null = null;

  constructor(nodeData: number) {
    this.data = nodeData;
  }

  public insert(nodeData: number): void {
    let current: BinarySearchTree = this;
    while (true) {
      if (nodeData > current.data) {
        if (current.right) {
          current = current.right;
        } else {
          current.right = new BinarySearchTree(nodeData);
          break;
        }
      } else {
        if (current.left) {
          current = current.left;
        } else {
          current.left = new BinarySearchTree(nodeData);
          break;
        }
      }
    }
  }

  public each(callback: (nodeData: number) => number): void {
    const stack: BinarySearchTree[] = [];
    let current: BinarySearchTree | null = this;

    while (stack.length > 0 || current) {
      while (current) {
        stack.push(current);
        current = current.left;
      }

      current = stack.pop()!;
      callback(current.data);
      current = current.right;
    }
  }
}