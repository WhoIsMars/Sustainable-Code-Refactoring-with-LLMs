def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(set(preorder)) \
            or len(inorder) != len(set(inorder)) \
            or set(preorder) != set(inorder):
        raise ValueError(r".+")

    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    return build_from_traversals(preorder, inorder, inorder_map, 0, len(preorder) - 1, 0, len(inorder) - 1)


def build_from_traversals(preorder, inorder, inorder_map, pre_start, pre_end, in_start, in_end):
    if pre_start > pre_end:
        return {}

    root_val = preorder[pre_start]
    root_index_inorder = inorder_map[root_val]

    left_subtree_size = root_index_inorder - in_start

    return {
        "v": root_val,
        "l": build_from_traversals(preorder, inorder, inorder_map, pre_start + 1, pre_start + left_subtree_size, in_start, root_index_inorder - 1),
        "r": build_from_traversals(preorder, inorder, inorder_map, pre_start + left_subtree_size + 1, pre_end, root_index_inorder + 1, in_end),
    }