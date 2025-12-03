public class DoublyLinkedList<T> {

    private Node first;
    private Node last;

    public void push(T value) {
        if (last == null) {
            addFirst(value);
        } else {
            Node newNode = new Node(value);
            last.next = newNode;
            newNode.previous = last;
            last = newNode;
        }
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
            first = null;
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
            last = null;
        }
        return value;
    }

    public void unshift(T value) {
        if (first == null) {
            addFirst(value);
        } else {
            Node newNode = new Node(value);
            first.previous = newNode;
            newNode.next = first;
            first = newNode;
        }
    }

    private void addFirst(T value) {
        Node newNode = new Node(value);
        first = newNode;
        last = newNode;
    }

    private class Node {
        private T value;
        private Node previous;
        private Node next;

        private Node(T value) {
            this.value = value;
        }
    }
}