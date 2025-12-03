export default class BinarySearchTree {
  public readonly data: number;
  public left: BinarySearchTree | null = null;
  public right: BinarySearchTree | null = null;

  constructor(nodeData: number) {
    this.data = nodeData;
  }

  public insert(nodeData: number): void {
    if (nodeData > this.data) {
      this.right ? this.right.insert(nodeData) : (this.right = new BinarySearchTree(nodeData));
    } else {
      this.left ? this.left.insert(nodeData) : (this.left = new BinarySearchTree(nodeData));
    }
  }

  public each(callback: (nodeData: number) => number): void {
    this.left?.each(callback);
    callback(this.data);
    this.right?.each(callback);
  }
}