public class DoublyLinkedList<T> {

    private Node first;
    private Node last;

    public void push(T value) {
        Node newNode = new Node(value, last, null);
        if (last == null) {
            first = newNode;
        } else {
            last.next = newNode;
        }
        last = newNode;
    }

    public T pop() {
        if (last == null) {
            return null;
        }
        T value = last.value;
        last = last.previous;
        if (last != null) {
            last.next = null;
        } else {
            first = null; // Clear first if list becomes empty
        }
        return value;
    }

    public T shift() {
        if (first == null) {
            return null;
        }
        T value = first.value;
        first = first.next;
        if (first != null) {
            first.previous = null;
        } else {
            last = null; // Clear last if list becomes empty
        }
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