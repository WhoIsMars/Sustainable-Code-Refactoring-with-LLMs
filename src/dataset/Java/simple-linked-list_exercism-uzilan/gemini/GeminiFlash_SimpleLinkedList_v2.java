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
            push(values[i]);
        }
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
        if (head == null || head.next == null) {
            return;
        }

        Node prev = null;
        Node current = head;
        Node next = null;

        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        head = prev;
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