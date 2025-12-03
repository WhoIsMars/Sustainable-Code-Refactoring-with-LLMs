import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Predicate;

class ListOps {

    static <T> List<T> append(List<T> list1, List<T> list2) {
        List<T> list = new ArrayList<>(list1.size() + list2.size());
        list.addAll(list1);
        list.addAll(list2);
        return list;
    }

    static <T> List<T> concat(List<List<T>> listOfLists) {
        int totalSize = listOfLists.stream().mapToInt(List::size).sum();
        List<T> result = new ArrayList<>(totalSize);
        listOfLists.forEach(result::addAll);
        return result;
    }

    static <T> List<T> filter(List<T> list, Predicate<T> predicate) {
        List<T> result = new ArrayList<>();
        for (T item : list) {
            if (predicate.test(item)) {
                result.add(item);
            }
        }
        return result;
    }

    static <T> int size(List<T> list) {
        return list.size();
    }

    static <T, U> List<U> map(List<T> list, Function<T, U> transform) {
        List<U> result = new ArrayList<>(list.size());
        for (T item : list) {
            result.add(transform.apply(item));
        }
        return result;
    }

    static <T> List<T> reverse(List<T> list) {
        List<T> newList = new ArrayList<>(list);
        Collections.reverse(newList);
        return newList;
    }

    static <T, U> U foldLeft(List<T> list, U initial, BiFunction<U, T, U> f) {
        U result = initial;
        for (T item : list) {
            result = f.apply(result, item);
        }
        return result;
    }

    static <T, U> U foldRight(List<T> list, U initial, BiFunction<T, U, U> f) {
        U result = initial;
        for (int i = list.size() - 1; i >= 0; i--) {
            result = f.apply(list.get(i), result);
        }
        return result;
    }

    private ListOps() {
        // No instances.
    }
}