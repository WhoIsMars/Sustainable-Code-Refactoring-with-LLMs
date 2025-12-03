import java.lang.reflect.Array;
import java.util.NoSuchElementException;

public class SimpleLinkedList<T> {

    private Node head;
    private int size; // Cache the size to avoid recalculating

    public SimpleLinkedList() {
        this.size = 0;
    }

    public SimpleLinkedList(final T[] values) {
        for (int i = values.length - 1; i >= 0; i--) { // Reverse iteration to avoid multiple head updates
            push(values[i]);
        }
    }

    public int size() {
        return size; // Return cached size
    }

    public T pop() {
        if (head == null) {
            throw new NoSuchElementException();
        }
        T value = head.value;
        head = head.next;
        size--; // Update size
        return value;
    }

    public void push(final T value) {
        head = new Node(value, head);
        size++; // Update size
    }

    public void reverse() {
        if (head == null || head.next == null) return; // No need to reverse if list is empty or has one element

        Node previous = null;
        Node current = head;

        while (current != null) {
            Node next = current.next; // Inline variable declaration
            current.next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    public T[] asArray(final Class<T> clazz) {
        T[] array = (T[]) Array.newInstance(clazz, size); // Use cached size
        Node node = head;
        for (int i = 0; i < size; i++) { // Use for loop for better readability
            array[i] = node.value;
            node = node.next;
        }
        return array;
    }

    private class Node {

        private final T value; // Mark as final since it doesn't change
        private Node next;

        private Node(final T value, final Node next) {
            this.value = value;
            this.next = next;
        }
    }
}