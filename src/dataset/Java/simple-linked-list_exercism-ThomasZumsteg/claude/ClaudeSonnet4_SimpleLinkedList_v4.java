import java.util.NoSuchElementException;
import java.lang.reflect.Array;

public class SimpleLinkedList<T> {
    private Element<T> root = null;
    private int size = 0;

    public SimpleLinkedList() { }

    public SimpleLinkedList(T[] values) {
        if (values != null && values.length > 0) {
            for (int i = values.length - 1; i >= 0; i--) {
                Element<T> e = new Element<T>(values[i], root);
                root = e;
                size++;
            }
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
       root = new Element<T>(value, root);
       size++;
   }

   public T[] asArray(Class<T> type) {
       if (size == 0) {
           return (T[])Array.newInstance(type, 0);
       }
       T[] array = (T[])Array.newInstance(type, size);
       Element<T> e = root;
       for (int i = 0; i < size; i++) {
           array[i] = e.value;
           e = e.next;
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
    
    public Element(T value, Element<T> next) {
        this.value = value;
        this.next = next;
    }
}