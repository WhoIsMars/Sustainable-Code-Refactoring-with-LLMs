#include "list_ops.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *list = (list_t *)malloc(sizeof(list_t) + length * sizeof(list_element_t));
    if (!list) return NULL;

    list->length = length;
    if (elements && length > 0)
    {
        memcpy(list->elements, elements, length * sizeof(list_element_t));
    }

    return list;
}

list_t *append_list(list_t *list1, list_t *list2)
{
    size_t new_length = list1->length + list2->length;
    list_t *list = (list_t *)malloc(sizeof(list_t) + new_length * sizeof(list_element_t));
    if (!list) return NULL;

    list->length = new_length;
    memcpy(list->elements, list1->elements, list1->length * sizeof(list_element_t));
    memcpy(list->elements + list1->length, list2->elements, list2->length * sizeof(list_element_t));

    return list;
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    list_element_t *temp_elements = (list_element_t *)malloc(list->length * sizeof(list_element_t));
    if (!temp_elements) return NULL;

    size_t count = 0;
    for (size_t i = 0; i < list->length; i++)
    {
        if (filter(list->elements[i]))
        {
            temp_elements[count++] = list->elements[i];
        }
    }

    list_t *filtered_list = new_list(count, temp_elements);
    free(temp_elements);
    return filtered_list;
}

size_t length_list(list_t *list)
{
    return list->length;
}

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    list_t *mapped_list = (list_t *)malloc(sizeof(list_t) + list->length * sizeof(list_element_t));
    if (!mapped_list) return NULL;

    mapped_list->length = list->length;
    for (size_t i = 0; i < list->length; i++)
    {
        mapped_list->elements[i] = map(list->elements[i]);
    }

    return mapped_list;
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t, list_element_t))
{
    list_element_t result = initial;
    for (size_t i = 0; i < list->length; i++)
    {
        result = foldl(list->elements[i], result);
    }
    return result;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t, list_element_t))
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
    list_t *reversed_list = (list_t *)malloc(sizeof(list_t) + list->length * sizeof(list_element_t));
    if (!reversed_list) return NULL;

    reversed_list->length = list->length;
    for (size_t i = 0; i < list->length; i++)
    {
        reversed_list->elements[i] = list->elements[list->length - 1 - i];
    }

    return reversed_list;
}

void delete_list(list_t *list)
{
    free(list);
}