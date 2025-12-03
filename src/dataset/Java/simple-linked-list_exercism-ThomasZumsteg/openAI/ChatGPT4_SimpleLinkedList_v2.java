import java.util.NoSuchElementException;
import java.lang.reflect.Array;

public class SimpleLinkedList<T> {
    private Element<T> root = null;
    private int size = 0; // Use primitive int to avoid unnecessary boxing/unboxing

    public SimpleLinkedList() { }

    public SimpleLinkedList(T[] values) {
        for (int i = values.length - 1; i >= 0; i--) { // Reverse iteration to avoid multiple shifts
            push(values[i]);
        }
    }

    public int size() { // Use primitive int for size
        return size;
    }

    public T pop() {
        if (root == null) {
            throw new NoSuchElementException();
        }
        T value = root.value;
        root = root.next;
        size--;
        return value;
    }

    public void push(T value) {
        root = new Element<>(value, root); // Inline element creation
        size++;
    }

    public T[] asArray(Class<T> type) {
        T[] array = (T[]) Array.newInstance(type, size);
        Element<T> current = root;
        for (int i = 0; i < size; i++) { // Use size directly to avoid recalculating
            array[i] = current.value;
            current = current.next;
        }
        return array;
    }

    public void reverse() {
        Element<T> prev = null;
        Element<T> current = root;
        while (current != null) {
            Element<T> next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        root = prev;
    }
}

class Element<T> {
    public T value;
    public Element<T> next;

    public Element(T value, Element<T> next) { // Constructor for cleaner initialization
        this.value = value;
        this.next = next;
    }
}