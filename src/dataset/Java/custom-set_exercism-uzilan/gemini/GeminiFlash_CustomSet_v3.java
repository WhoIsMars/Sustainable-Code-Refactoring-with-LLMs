import java.util.Collection;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class CustomSet<T> {

    private final Set<T> data;

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
        return data.containsAll(other.data);
    }

    public boolean isDisjoint(CustomSet<T> other) {
        if (data.size() > other.data.size()) {
            return other.data.stream().noneMatch(data::contains);
        } else {
            return data.stream().noneMatch(other.data::contains);
        }
    }

    public void add(T element) {
        data.add(element);
    }

    public CustomSet<T> getIntersection(CustomSet<T> other) {
        Set<T> smallerSet = data.size() <= other.data.size() ? data : other.data;
        Set<T> largerSet = data.size() > other.data.size() ? data : other.data;
        Set<T> intersection = new HashSet<>();

        for (T element : smallerSet) {
            if (largerSet.contains(element)) {
                intersection.add(element);
            }
        }
        return new CustomSet<>(intersection);
    }

    public CustomSet<T> getDifference(CustomSet<T> other) {
        Set<T> difference = new HashSet<>(data);
        difference.removeAll(other.data);
        return new CustomSet<>(difference);
    }

    public CustomSet<T> getUnion(CustomSet<T> other) {
        Set<T> union = new HashSet<>(data);
        union.addAll(other.data);
        return new CustomSet<>(union);
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof CustomSet)) {
            return false;
        }
        CustomSet<?> otherSet = (CustomSet<?>) other;
        return data.equals(otherSet.data);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(data);
    }
}