public class DoublyLinkedList<T> {

    private Node first;
    private Node last;
    private int size;

    public void push(T value) {
        final Node newNode = new Node(value, last, null);
        if (first == null) {
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
        final T value = last.value;
        final Node prevNode = last.previous;
        
        last.value = null;
        last.previous = null;
        
        last = prevNode;
        if (last != null) {
            last.next = null;
        } else {
            first = null;
        }
        size--;
        return value;
    }

    public T shift() {
        if (first == null) {
            return null;
        }
        final T value = first.value;
        final Node nextNode = first.next;
        
        first.value = null;
        first.next = null;
        
        first = nextNode;
        if (first != null) {
            first.previous = null;
        } else {
            last = null;
        }
        size--;
        return value;
    }

    public void unshift(T value) {
        final Node newNode = new Node(value, null, first);
        if (first == null) {
            last = newNode;
        } else {
            first.previous = newNode;
        }
        first = newNode;
        size++;
    }

    private static final class Node {
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