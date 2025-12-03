def triplets_with_sum(number):
    triplets = []
    
    for a in range(1, number // 3):
        a_squared = a * a
        target = number - a
        
        for b in range(a + 1, (target + 1) // 2):
            c = target - b
            if c <= b:
                break
            
            b_squared = b * b
            c_squared = c * c
            
            if a_squared + b_squared == c_squared:
                triplets.append([a, b, c])
    
    return triplets