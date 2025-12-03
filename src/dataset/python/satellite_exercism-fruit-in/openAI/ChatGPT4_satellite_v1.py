def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(set(preorder)) \
            or len(inorder) != len(set(inorder)) \
            or set(preorder) != set(inorder):
        raise ValueError(r".+")

    inorder_index = {value: idx for idx, value in enumerate(inorder)}
    return build_from_traversals(preorder, inorder_index, 0, len(preorder) - 1, 0, len(inorder) - 1)


def build_from_traversals(preorder, inorder_index, pre_start, pre_end, in_start, in_end):
    if pre_start > pre_end or in_start > in_end:
        return {}

    root_val = preorder[pre_start]
    root_idx = inorder_index[root_val]
    left_size = root_idx - in_start

    return {
        "v": root_val,
        "l": build_from_traversals(preorder, inorder_index, pre_start + 1, pre_start + left_size, in_start, root_idx - 1),
        "r": build_from_traversals(preorder, inorder_index, pre_start + left_size + 1, pre_end, root_idx + 1, in_end),
    }