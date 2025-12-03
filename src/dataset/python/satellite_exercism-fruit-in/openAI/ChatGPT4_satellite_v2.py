def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(set(preorder)) \
            or len(inorder) != len(set(inorder)) \
            or set(preorder) != set(inorder):
        raise ValueError(r".+")

    inorder_index_map = {value: idx for idx, value in enumerate(inorder)}
    return build_from_traversals(preorder, inorder_index_map, 0, 0, len(preorder))


def build_from_traversals(preorder, inorder_index_map, pre_start, in_start, length):
    if length == 0:
        return {}

    root_value = preorder[pre_start]
    root_index = inorder_index_map[root_value]
    left_length = root_index - in_start

    return {
        "v": root_value,
        "l": build_from_traversals(preorder, inorder_index_map, pre_start + 1, in_start, left_length),
        "r": build_from_traversals(preorder, inorder_index_map, pre_start + 1 + left_length, root_index + 1, length - left_length - 1),
    }