import java.util.NoSuchElementException;
import java.lang.reflect.Array;

public class SimpleLinkedList<T> {
    private Element<T> root = null;
    private int size = 0;

    //SimpleLinkedList creates a linked list with no values
    public SimpleLinkedList() { }

    public SimpleLinkedList(T[] values) {
        //SimpleLinkedList creates a linked list from an array of values
        for(int i = values.length - 1; i >= 0; i--) {
            Element<T> e = new Element<T>(values[i], root);
            root = e;
            size++;
        }
    }

   public Integer size() {
       //size the size of the linked list
       return size;
   } 

   public T pop() throws NoSuchElementException {
       //pop return and remove the top element of the linked list
       if(root == null)
           throw new NoSuchElementException();
       T value = root.value;
       root = root.next;
       size--;
       return value;
   }
       
   public void push(T value) {
       //push adds a new element to the top of the linked list
       root = new Element<T>(value, root);
       size++;
   }

   public T[] asArray(Class<T> type) {
       //asArray creates an array from the linked list
       T[] array = (T[])Array.newInstance(type, size);
       Element<T> e = root;
       for(int i = 0; e != null; e = e.next, i++)
           array[i] = e.value;
       return array;
   }

   public void reverse() {
       //reverse puts the elements of the linked list in the opposite order
       if(root == null || root.next == null) return;
       
       Element<T> prev = null;
       Element<T> current = root;
       Element<T> next;
       
       while(current != null) {
           next = current.next;
           current.next = prev;
           prev = current;
           current = next;
       }
       root = prev;
    }
}

class Element<T> {
    //Element is an element in the linked list
    public final T value;
    public Element<T> next;
    
    public Element(T value, Element<T> next) {
        this.value = value;
        this.next = next;
    }
}