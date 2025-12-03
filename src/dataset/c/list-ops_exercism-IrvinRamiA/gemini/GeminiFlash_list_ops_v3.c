#include "list_ops.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

list_t *new_list(size_t length, list_element_t elements[]) {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  if (list == NULL) {
    return NULL; // Handle allocation failure
  }

  list->length = length;
  list->elements = (list_element_t *)malloc(length * sizeof(list_element_t));

  if (length > 0 && elements != NULL) {
    if (list->elements == NULL) {
      free(list);
      return NULL; // Handle allocation failure
    }
    memcpy(list->elements, elements, length * sizeof(list_element_t));
  } else {
    list->elements = NULL;
  }

  return list;
}

list_t *append_list(list_t *list1, list_t *list2) {
  size_t new_length = list1->length + list2->length;
  list_t *new_list_ptr = (list_t *)malloc(sizeof(list_t));

  if (new_list_ptr == NULL) {
    return NULL; // Handle allocation failure
  }

  new_list_ptr->length = new_length;
  new_list_ptr->elements =
      (list_element_t *)malloc(new_length * sizeof(list_element_t));

  if (new_list_ptr->elements == NULL) {
    free(new_list_ptr);
    return NULL; // Handle allocation failure
  }

  memcpy(new_list_ptr->elements, list1->elements,
         list1->length * sizeof(list_element_t));
  memcpy(new_list_ptr->elements + list1->length, list2->elements,
         list2->length * sizeof(list_element_t));

  return new_list_ptr;
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t)) {
  size_t filtered_length = 0;
  list_element_t *filtered_elements =
      (list_element_t *)malloc(list->length * sizeof(list_element_t));
  if (filtered_elements == NULL) {
    return new_list(0, NULL); // Return empty list on allocation failure
  }

  for (size_t i = 0; i < list->length; i++) {
    if (filter(list->elements[i])) {
      filtered_elements[filtered_length++] = list->elements[i];
    }
  }

  list_t *filtered_list = new_list(filtered_length, filtered_elements);
  free(filtered_elements);
  return filtered_list;
}

size_t length_list(list_t *list) { return list->length; }

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t)) {
  list_t *mapped_list = new_list(list->length, NULL);
  if (mapped_list == NULL) {
    return NULL; // Handle allocation failure
  }

  if (list->length > 0) {
    mapped_list->elements =
        (list_element_t *)malloc(list->length * sizeof(list_element_t));
    if (mapped_list->elements == NULL) {
      free(mapped_list);
      return NULL; // Handle allocation failure
    }

    for (size_t i = 0; i < list->length; i++) {
      mapped_list->elements[i] = map(list->elements[i]);
    }
  }

  return mapped_list;
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t)) {
  list_element_t result = initial;
  for (size_t i = 0; i < list->length; i++) {
    result = foldl(result, list->elements[i]);
  }
  return result;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t)) {
  list_element_t result = initial;
  for (size_t i = list->length; i > 0; i--) {
    result = foldr(list->elements[i - 1], result);
  }
  return result;
}

list_t *reverse_list(list_t *list) {
  list_t *reversed_list = new_list(list->length, NULL);

  if (reversed_list == NULL) {
    return NULL; // Handle allocation failure
  }

  if (list->length > 0) {
    reversed_list->elements =
        (list_element_t *)malloc(list->length * sizeof(list_element_t));

    if (reversed_list->elements == NULL) {
      free(reversed_list);
      return NULL; // Handle allocation failure
    }

    for (size_t i = 0; i < list->length; i++) {
      reversed_list->elements[i] = list->elements[list->length - 1 - i];
    }
  }

  return reversed_list;
}

void delete_list(list_t *list) {
  if (list != NULL) {
    if (list->elements != NULL) {
      free(list->elements);
    }
    free(list);
  }
}