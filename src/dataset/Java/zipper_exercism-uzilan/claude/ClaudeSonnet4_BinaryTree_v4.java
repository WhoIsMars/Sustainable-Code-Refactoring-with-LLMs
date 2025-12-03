import java.util.Objects;

public class BinaryTree {

    private final Zipper root;
    private volatile int hashCode;

    public BinaryTree(Zipper zipper) {
        root = zipper;
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
        if (o == null || getClass() != o.getClass()) return false;
        return Objects.equals(root, ((BinaryTree) o).root);
    }

    @Override
    public int hashCode() {
        int result = hashCode;
        if (result == 0) {
            result = Objects.hash(root);
            hashCode = result;
        }
        return result;
    }
}