public class DoublyLinkedList<T> {

    private Node first;
    private Node last;
    private int size;

    public void push(T value) {
        Node newNode = new Node(value, last, null);
        if (last == null) {
            first = newNode;
        } else {
            last.next = newNode;
        }
        last = newNode;
        size++;
    }

    public T pop() {
        if (last == null) {
            return null;
        }
        T value = last.value;
        last = last.previous;
        if (last == null) {
            first = null;
        } else {
            last.next = null;
        }
        size--;
        return value;
    }

    public T shift() {
        if (first == null) {
            return null;
        }
        T value = first.value;
        first = first.next;
        if (first == null) {
            last = null;
        } else {
            first.previous = null;
        }
        size--;
        return value;
    }

    public void unshift(T value) {
        Node newNode = new Node(value, null, first);
        if (first == null) {
            last = newNode;
        } else {
            first.previous = newNode;
        }
        first = newNode;
        size++;
    }

    public int size() {
        return size;
    }

    private class Node {

        private final T value;
        private Node previous;
        private Node next;

        private Node(T value, Node previous, Node next) {
            this.value = value;
            this.previous = previous;
            this.next = next;
        }
    }
}