class Flattener {
    flatten(array) {
        if (array == null) return [];
        if (!Array.isArray(array)) return [array];
        
        const result = [];
        const stack = [array];
        
        while (stack.length > 0) {
            const current = stack.pop();
            
            for (let i = current.length - 1; i >= 0; i--) {
                const element = current[i];
                if (Array.isArray(element)) {
                    stack.push(element);
                } else {
                    result.unshift(element);
                }
            }
        }
        
        return result;
    }
}

module.exports = Flattener;