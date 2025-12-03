def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(inorder) or set(preorder) != set(inorder):
        raise ValueError("Invalid traversals: preorder and inorder must have the same elements and length.")

    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    return build_tree(preorder, inorder_map, 0, 0, len(inorder))


def build_tree(preorder, inorder_map, pre_start, in_start, in_end):
    if in_start == in_end:
        return {}

    root_val = preorder[pre_start]
    root_idx = inorder_map[root_val]

    left_size = root_idx - in_start

    return {
        "v": root_val,
        "l": build_tree(preorder, inorder_map, pre_start + 1, in_start, root_idx),
        "r": build_tree(preorder, inorder_map, pre_start + 1 + left_size, root_idx + 1, in_end),
    }