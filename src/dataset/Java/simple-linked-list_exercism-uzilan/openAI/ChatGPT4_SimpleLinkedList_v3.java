import java.lang.reflect.Array;
import java.util.NoSuchElementException;

public class SimpleLinkedList<T> {

    private Node head;
    private int size;

    public SimpleLinkedList() {
        this.size = 0;
    }

    public SimpleLinkedList(final T[] values) {
        for (int i = values.length - 1; i >= 0; i--) {
            head = new Node(values[i], head);
        }
        this.size = values.length;
    }

    public int size() {
        return size;
    }

    public T pop() {
        if (head == null) {
            throw new NoSuchElementException();
        }
        T value = head.value;
        head = head.next;
        size--;
        return value;
    }

    public void push(final T value) {
        head = new Node(value, head);
        size++;
    }

    public void reverse() {
        Node previous = null;
        Node current = head;

        while (current != null) {
            Node next = current.next;
            current.next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    public T[] asArray(final Class<T> clazz) {
        T[] array = (T[]) Array.newInstance(clazz, size);
        Node node = head;
        for (int i = 0; i < size; i++) {
            array[i] = node.value;
            node = node.next;
        }
        return array;
    }

    private class Node {

        private final T value;
        private Node next;

        private Node(final T value, final Node next) {
            this.value = value;
            this.next = next;
        }
    }
}