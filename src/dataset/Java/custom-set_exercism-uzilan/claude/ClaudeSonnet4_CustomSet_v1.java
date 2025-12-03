import java.util.Collection;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class CustomSet<T> {

    private Set<T> data;

    public CustomSet(Collection<T> collection) {
        data = new HashSet<>(collection);
    }

    public boolean isEmpty() {
        return data.isEmpty();
    }

    public boolean contains(T item) {
        return data.contains(item);
    }

    public boolean isSubset(CustomSet<T> other) {
        return other.data.containsAll(data);
    }

    public boolean isDisjoint(CustomSet<T> other) {
        Set<T> smaller = data.size() <= other.data.size() ? data : other.data;
        Set<T> larger = data.size() > other.data.size() ? data : other.data;
        
        for (T element : smaller) {
            if (larger.contains(element)) {
                return false;
            }
        }
        return true;
    }

    public void add(T element) {
        data.add(element);
    }

    public CustomSet<T> getIntersection(CustomSet<T> other) {
        Set<T> smaller = data.size() <= other.data.size() ? data : other.data;
        Set<T> larger = data.size() > other.data.size() ? data : other.data;
        
        final Set<T> newSet = new HashSet<>();
        for (T element : smaller) {
            if (larger.contains(element)) {
                newSet.add(element);
            }
        }
        return new CustomSet<>(newSet);
    }

    public CustomSet<T> getDifference(CustomSet<T> other) {
        final Set<T> newSet = new HashSet<>();
        for (T element : data) {
            if (!other.data.contains(element)) {
                newSet.add(element);
            }
        }
        return new CustomSet<>(newSet);
    }

    public CustomSet<T> getUnion(CustomSet<T> other) {
        final Set<T> newSet = new HashSet<>(data);
        newSet.addAll(other.data);
        return new CustomSet<>(newSet);
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || getClass() != other.getClass()) {
            return false;
        }
        Set<?> otherData = ((CustomSet<?>) other).data;
        return data.size() == otherData.size() && data.equals(otherData);
    }

    @Override
    public int hashCode() {
        return Objects.hash(data);
    }
}