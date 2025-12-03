def spiral(size):
    if size <= 0:
        return []
    
    result = [[0] * size for _ in range(size)]
    
    top, bottom = 0, size - 1
    left, right = 0, size - 1
    num = 1
    
    while top <= bottom and left <= right:
        for col in range(left, right + 1):
            result[top][col] = num
            num += 1
        top += 1
        
        for row in range(top, bottom + 1):
            result[row][right] = num
            num += 1
        right -= 1
        
        if top <= bottom:
            for col in range(right, left - 1, -1):
                result[bottom][col] = num
                num += 1
            bottom -= 1
        
        if left <= right:
            for row in range(bottom, top - 1, -1):
                result[row][left] = num
                num += 1
            left += 1
    
    return result