import java.util.NoSuchElementException;
import java.lang.reflect.Array;
import java.util.Objects;

public class SimpleLinkedList<T> {
    private Element<T> root = null;
    private int size = 0;

    public SimpleLinkedList() { }

    public SimpleLinkedList(T[] values) {
        if (values != null && values.length > 0) {
            for (int i = values.length - 1; i >= 0; i--) {
                push(values[i]);
            }
        }
    }

   public int size() {
       return size;
   }

   public T pop() {
       if (root == null) {
           throw new NoSuchElementException();
       }
       T value = root.value;
       root = root.next;
       size--;
       return value;
   }

   public void push(T value) {
       Element<T> newElement = new Element<>();
       newElement.value = value;
       newElement.next = root;
       root = newElement;
       size++;
   }

   public T[] asArray(Class<T> type) {
       if (size == 0) {
           return (T[]) Array.newInstance(type, 0);
       }

       T[] array = (T[]) Array.newInstance(type, size);
       Element<T> current = root;
       int i = 0;
       while (current != null) {
           array[i++] = current.value;
           current = current.next;
       }
       return array;
   }


   public void reverse() {
        if (root == null || root.next == null) {
            return; // Nothing to reverse if empty or only one element
        }

        Element<T> prev = null;
        Element<T> current = root;
        Element<T> next = null;

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
    public T value;
    public Element<T> next;
}