def triplets_with_sum(number):
    triplets = []
    
    for a in range(1, number // 3):
        remaining = number - a
        b_max = remaining // 2
        
        for b in range(a + 1, b_max + 1):
            c = remaining - b
            
            if c <= b:
                break
                
            a_sq = a * a
            b_sq = b * b
            c_sq = c * c
            
            if a_sq + b_sq == c_sq:
                triplets.append([a, b, c])
    
    return triplets