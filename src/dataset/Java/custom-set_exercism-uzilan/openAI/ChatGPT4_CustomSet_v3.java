import java.util.Collection;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class CustomSet<T> {

    private final Set<T> data;

    public CustomSet(Collection<T> collection) {
        this.data = new HashSet<>(collection);
    }

    public boolean isEmpty() {
        return data.isEmpty();
    }

    public boolean contains(T item) {
        return data.contains(item);
    }

    public boolean isSubset(CustomSet<T> other) {
        return other.data.size() >= data.size() && other.data.containsAll(data);
    }

    public boolean isDisjoint(CustomSet<T> other) {
        for (T item : data) {
            if (other.data.contains(item)) {
                return false;
            }
        }
        return true;
    }

    public void add(T element) {
        data.add(element);
    }

    public CustomSet<T> getIntersection(CustomSet<T> other) {
        Set<T> newSet = new HashSet<>();
        for (T item : data) {
            if (other.data.contains(item)) {
                newSet.add(item);
            }
        }
        return new CustomSet<>(newSet);
    }

    public CustomSet<T> getDifference(CustomSet<T> other) {
        Set<T> newSet = new HashSet<>(data);
        newSet.removeAll(other.data);
        return new CustomSet<>(newSet);
    }

    public CustomSet<T> getUnion(CustomSet<T> other) {
        Set<T> newSet = new HashSet<>(data);
        newSet.addAll(other.data);
        return new CustomSet<>(newSet);
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof CustomSet<?>)) {
            return false;
        }
        CustomSet<?> otherSet = (CustomSet<?>) other;
        return data.equals(otherSet.data);
    }

    @Override
    public int hashCode() {
        return data.hashCode();
    }
}