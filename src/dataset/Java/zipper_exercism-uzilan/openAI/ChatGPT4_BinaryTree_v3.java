import java.util.Objects;

public class BinaryTree {

    private final Zipper root;

    public BinaryTree(Zipper zipper) {
        this.root = Objects.requireNonNull(zipper, "Zipper cannot be null");
    }

    public BinaryTree(int i) {
        this(new Zipper(i));
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
        return root.equals(((BinaryTree) o).root);
    }

    @Override
    public int hashCode() {
        return root.hashCode();
    }
}