def triplets_with_sum(number):
    triplets = []
    
    for a in range(1, number // 3):
        b_squared = (number * number - 2 * a * number) // (2 * (number - a))
        b = int(b_squared ** 0.5)
        
        if b <= a:
            continue
            
        c = number - a - b
        
        if c <= b:
            continue
            
        if a * a + b * b == c * c:
            triplets.append([a, b, c])
    
    return triplets