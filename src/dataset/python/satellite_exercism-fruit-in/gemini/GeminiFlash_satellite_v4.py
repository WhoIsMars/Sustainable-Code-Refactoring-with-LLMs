def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(set(preorder)) \
            or len(inorder) != len(set(inorder)) \
            or set(preorder) != set(inorder):
        raise ValueError(r".+")

    return build_from_traversals(preorder, inorder, 0, len(inorder))


def build_from_traversals(preorder, inorder, inorder_start, inorder_end):
    if inorder_start >= inorder_end:
        return {}

    root_val = preorder.pop(0)
    root_index_inorder = inorder.index(root_val)

    left_subtree = build_from_traversals(preorder, inorder, inorder_start, root_index_inorder)
    right_subtree = build_from_traversals(preorder, inorder, root_index_inorder + 1, inorder_end)

    return {
        "v": root_val,
        "l": left_subtree,
        "r": right_subtree,
    }