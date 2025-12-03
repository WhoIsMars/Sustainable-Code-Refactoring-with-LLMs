import java.util.NoSuchElementException;
import java.lang.reflect.Array;

public class SimpleLinkedList<T> {
    private Element<T> root = null;
    private int size = 0;

    public SimpleLinkedList() { }

    public SimpleLinkedList(T[] values) {
        if (values != null && values.length > 0) {
            for (int i = values.length - 1; i >= 0; i--) {
                Element<T> e = new Element<>(values[i]);
                e.next = root;
                root = e;
            }
            size = values.length;
        }
    }

    public Integer size() {
        return size;
    } 

    public T pop() throws NoSuchElementException {
        if (root == null)
            throw new NoSuchElementException();
        T value = root.value;
        root = root.next;
        size--;
        return value;
    }
       
    public void push(T value) {
        Element<T> e = new Element<>(value);
        e.next = root;
        root = e;
        size++;
    }

    public T[] asArray(Class<T> type) {
        @SuppressWarnings("unchecked")
        T[] array = (T[])Array.newInstance(type, size);
        Element<T> current = root;
        for (int i = 0; current != null; current = current.next, i++) {
            array[i] = current.value;
        }
        return array;
    }

    public void reverse() {
        if (root == null || root.next == null) return;
        
        Element<T> prev = null;
        Element<T> current = root;
        Element<T> next;
        
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        root = prev;
    }
}

class Element<T> {
    public final T value;
    public Element<T> next;
    
    public Element(T value) {
        this.value = value;
    }
}