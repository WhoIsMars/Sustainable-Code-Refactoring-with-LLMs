def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(inorder) or len(set(preorder)) != len(preorder):
        raise ValueError("Invalid input: Preorder and inorder traversals must have the same length and contain unique elements.")

    if set(preorder) != set(inorder):
        raise ValueError("Invalid input: Preorder and inorder traversals must contain the same elements.")

    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    return build_from_traversals(preorder, inorder_map, 0, len(inorder) - 1, [0])


def build_from_traversals(preorder, inorder_map, inorder_start, inorder_end, preorder_index):
    if inorder_start > inorder_end:
        return {}

    root_val = preorder[preorder_index[0]]
    root_index_inorder = inorder_map[root_val]

    preorder_index[0] += 1

    node = {
        "v": root_val,
        "l": build_from_traversals(preorder, inorder_map, inorder_start, root_index_inorder - 1, preorder_index),
        "r": build_from_traversals(preorder, inorder_map, root_index_inorder + 1, inorder_end, preorder_index),
    }
    return node