def tree_from_traversals(preorder, inorder):
    if len(preorder) != len(inorder):
        raise ValueError(r".+")
    
    preorder_set = set(preorder)
    inorder_set = set(inorder)
    
    if len(preorder) != len(preorder_set) \
            or len(inorder) != len(inorder_set) \
            or preorder_set != inorder_set:
        raise ValueError(r".+")

    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    return build_from_traversals(preorder, inorder, inorder_map, 0, len(preorder), 0, len(inorder))


def build_from_traversals(preorder, inorder, inorder_map=None, pre_start=0, pre_end=0, in_start=0, in_end=0):
    if inorder_map is None:
        if not preorder:
            return {}
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        return build_from_traversals(preorder, inorder, inorder_map, 0, len(preorder), 0, len(inorder))
    
    if pre_start >= pre_end:
        return {}

    root_val = preorder[pre_start]
    root_idx = inorder_map[root_val]
    
    left_size = root_idx - in_start

    return {
        "v": root_val,
        "l": build_from_traversals(preorder, inorder, inorder_map, pre_start + 1, pre_start + 1 + left_size, in_start, root_idx),
        "r": build_from_traversals(preorder, inorder, inorder_map, pre_start + 1 + left_size, pre_end, root_idx + 1, in_end),
    }