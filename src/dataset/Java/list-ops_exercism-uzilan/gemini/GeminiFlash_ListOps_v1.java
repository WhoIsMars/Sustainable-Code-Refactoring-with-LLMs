import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Predicate;

class ListOps {

    static <T> List<T> append(List<T> list1, List<T> list2) {
        List<T> result = new ArrayList<>(list1.size() + list2.size());
        result.addAll(list1);
        result.addAll(list2);
        return result;
    }

    static <T> List<T> concat(List<List<T>> listOfLists) {
        List<T> result = new ArrayList<>();
        for (List<T> list : listOfLists) {
            result.addAll(list);
        }
        return result;
    }

    static <T> List<T> filter(List<T> list, Predicate<T> predicate) {
        List<T> result = new ArrayList<>();
        for (T element : list) {
            if (predicate.test(element)) {
                result.add(element);
            }
        }
        return result;
    }

    static <T> int size(List<T> list) {
        return list.size();
    }

    static <T, U> List<U> map(List<T> list, Function<T, U> transform) {
        List<U> result = new ArrayList<>(list.size());
        for (T element : list) {
            result.add(transform.apply(element));
        }
        return result;
    }

    static <T> List<T> reverse(List<T> list) {
        List<T> result = new ArrayList<>(list);
        Collections.reverse(result);
        return result;
    }

    static <T, U> U foldLeft(List<T> list, U initial, BiFunction<U, T, U> f) {
        U accumulator = initial;
        for (T element : list) {
            accumulator = f.apply(accumulator, element);
        }
        return accumulator;
    }

    static <T, U> U foldRight(List<T> list, U initial, BiFunction<T, U, U> f) {
        U accumulator = initial;
        for (int i = list.size() - 1; i >= 0; i--) {
            accumulator = f.apply(list.get(i), accumulator);
        }
        return accumulator;
    }

    private ListOps() {
        // No instances.
    }
}