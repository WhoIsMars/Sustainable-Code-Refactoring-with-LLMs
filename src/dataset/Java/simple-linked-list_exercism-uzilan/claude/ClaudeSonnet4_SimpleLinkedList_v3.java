import java.lang.reflect.Array;
import java.util.NoSuchElementException;

public class SimpleLinkedList<T> {

    private Node head;
    private int size;

    public SimpleLinkedList() {
        this.size = 0;
    }

    public SimpleLinkedList(final T[] values) {
        this.size = 0;
        for (T value : values) {
            head = new Node(value, head);
            size++;
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
        for (int i = 0; i < size && node != null; i++) {
            array[i] = node.value;
            node = node.next;
        }
        return array;
    }

    private static class Node<T> {
        private T value;
        private Node<T> next;

        private Node(final T value, final Node<T> next) {
            this.value = value;
            this.next = next;
        }
    }
}