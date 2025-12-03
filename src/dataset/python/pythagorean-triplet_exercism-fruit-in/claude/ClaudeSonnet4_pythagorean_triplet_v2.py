def triplets_with_sum(number):
    triplets = []
    a_squared_cache = {}
    
    for a in range(1, number // 3):
        if a not in a_squared_cache:
            a_squared_cache[a] = a * a
        a_squared = a_squared_cache[a]
        
        l = a + 1
        r = (number - a - 1) // 2

        while l <= r:
            b = (l + r) // 2
            c = number - a - b
            
            b_squared = b * b
            c_squared = c * c
            sum_squares = a_squared + b_squared

            if sum_squares < c_squared:
                l = b + 1
            elif sum_squares > c_squared:
                r = b - 1
            else:
                triplets.append([a, b, c])
                break

    return triplets