import java.lang.reflect.Array;
import java.util.NoSuchElementException;

public class SimpleLinkedList<T> {

    private Node head;
    private int listSize;

    public SimpleLinkedList() {
        this.listSize = 0;
    }

    public SimpleLinkedList(final T[] values) {
        for (int i = values.length - 1; i >= 0; i--) {
            push(values[i]);
        }
    }

    public int size() {
        return listSize;
    }

    public T pop() {
        if (head == null) {
            throw new NoSuchElementException();
        }
        T value = head.value;
        head = head.next;
        listSize--;
        return value;
    }

    public void push(final T value) {
        head = new Node(value, head);
        listSize++;
    }

    public void reverse() {
        if (head == null || head.next == null) {
            return;
        }

        Node previous = null;
        Node current = head;
        Node next = null;

        while (current != null) {
            next = current.next;
            current.next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    public T[] asArray(final Class<T> clazz) {
        T[] array = (T[]) Array.newInstance(clazz, listSize);
        Node node = head;
        for (int i = 0; i < listSize; i++) {
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