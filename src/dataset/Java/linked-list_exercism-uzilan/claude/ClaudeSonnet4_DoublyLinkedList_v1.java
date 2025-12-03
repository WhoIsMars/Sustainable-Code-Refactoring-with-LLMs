public class DoublyLinkedList<T> {

    private Node first;
    private Node last;

    public void push(T value) {
        Node newNode = new Node(value, last, null);
        if (first == null) {
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
        final T value = last.value;
        last = last.previous;
        if (last != null) {
            last.next = null;
        } else {
            first = null;
        }
        return value;
    }

    public T shift() {
        if (first == null) {
            return null;
        }
        final T value = first.value;
        first = first.next;
        if (first != null) {
            first.previous = null;
        } else {
            last = null;
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

    private static class Node {
        private Object value;
        private Node previous;
        private Node next;

        private Node(Object value, Node previous, Node next) {
            this.value = value;
            this.previous = previous;
            this.next = next;
        }
    }
}