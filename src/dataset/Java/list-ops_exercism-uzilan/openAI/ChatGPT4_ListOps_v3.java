import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Predicate;

import static java.util.stream.Collectors.toCollection;

class ListOps {

    static <T> List<T> append(List<T> list1, List<T> list2) {
        List<T> result = new ArrayList<>(list1.size() + list2.size());
        result.addAll(list1);
        result.addAll(list2);
        return result;
    }

    static <T> List<T> concat(List<List<T>> listOfLists) {
        return listOfLists.stream()
                .flatMap(Collection::stream)
                .collect(toCollection(() -> new ArrayList<>(listOfLists.stream().mapToInt(List::size).sum())));
    }

    static <T> List<T> filter(List<T> list, Predicate<T> predicate) {
        return list.stream()
                .filter(predicate)
                .collect(toCollection(() -> new ArrayList<>(list.size())));
    }

    static <T> int size(List<T> list) {
        return list.size();
    }

    static <T, U> List<U> map(List<T> list, Function<T, U> transform) {
        return list.stream()
                .map(transform)
                .collect(toCollection(() -> new ArrayList<>(list.size())));
    }

    static <T> List<T> reverse(List<T> list) {
        List<T> newList = new ArrayList<>(list);
        Collections.reverse(newList);
        return newList;
    }

    static <T, U> U foldLeft(List<T> list, U initial, BiFunction<U, T, U> f) {
        U result = initial;
        for (T element : list) {
            result = f.apply(result, element);
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