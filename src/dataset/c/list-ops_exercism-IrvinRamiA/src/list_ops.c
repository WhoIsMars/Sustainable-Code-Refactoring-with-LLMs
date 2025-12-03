#include "list_ops.h"
#include <stdint.h>

list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *list = (list_t *)malloc(sizeof(list_t) + length * sizeof(list_element_t));

    list->length = length;

    for (uint8_t i = 0; i < length; i++)
    {
        list->elements[i] = elements[i];
    }

    return list;
}

list_t *append_list(list_t *list1, list_t *list2)
{
    list_element_t *elements = (list_element_t *)malloc((list1->length + list2->length) * sizeof(list_element_t));
    list_t *list = new_list(list1->length + list2->length, elements);

    for (uint8_t i = 0; i < list1->length; i++)
    {
        list->elements[i] = list1->elements[i];
    }
    for (uint8_t i = 0; i < list2->length; i++)
    {
        list->elements[list1->length + i] = list2->elements[i];
    }

    return list;
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    // list_element_t *elements = (list_element_t *)malloc(list->length * sizeof(list_element_t));
    list_t *filtered_list = new_list(0, NULL);

    for (uint8_t i = 0; i < list->length; i++)
    {
        if (filter(list->elements[i]))
        {
            filtered_list = append_list(filtered_list, new_list(1, &list->elements[i]));
        }
    }

    return filtered_list;
}

size_t length_list(list_t *list)
{
    return list->length;
}

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    list_t *mapped_list = new_list(0, NULL);
    list_element_t current_element[1];

    for (size_t i = 0; i < list->length; i++)
    {
        current_element[0] = map(list->elements[i]);
        mapped_list = append_list(mapped_list, new_list(1, current_element));
    }
    return mapped_list;
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t))
{
    list_element_t result = initial;
    for (size_t i = 0; i < list->length; i++)
    {
        result = foldl(list->elements[i], result);
    }
    return result;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t))
{
    list_element_t result = initial;
    for (size_t i = list->length; i > 0; i--)
    {
        result = foldr(list->elements[i - 1], result);
    }
    return result;
}

list_t *reverse_list(list_t *list)
{
    list_element_t *elements = (list_element_t *)malloc(list->length * sizeof(list_element_t));
    list_t *reversed_list = new_list(0, elements);

    for (uint8_t i = 0; i < list->length; i++)
    {
        reversed_list = append_list(reversed_list, new_list(1, &list->elements[list->length - 1 - i]));
    }

    return reversed_list;
}

void delete_list(list_t *list)
{
    free(list);
}
