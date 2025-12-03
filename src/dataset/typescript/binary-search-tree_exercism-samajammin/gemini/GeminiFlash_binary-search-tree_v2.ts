export default class BinarySearchTree {
  public readonly data: number;
  public left: BinarySearchTree | null;
  public right: BinarySearchTree | null;

  constructor(nodeData: number) {
    this.data = nodeData;
    this.left = null;
    this.right = null;
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

  public each(callback: (nodeData: number) => void): void {
    const traverse = (node: BinarySearchTree | null) => {
      if (node) {
        traverse(node.left);
        callback(node.data);
        traverse(node.right);
      }
    };

    traverse(this);
  }
}