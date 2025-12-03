import java.util.Objects;

public class BinaryTree {

    private final Zipper root;

    public BinaryTree(Zipper zipper) {
        root = zipper;
    }

    public BinaryTree(int i) {
        root = new Zipper(i);
    }

    public Zipper getRoot() {
        return root;
    }

    public String printTree() {
        return root.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof BinaryTree)) return false;
        return Objects.equals(root, ((BinaryTree) o).root);
    }

    @Override
    public int hashCode() {
        return root != null ? root.hashCode() : 0;
    }
}