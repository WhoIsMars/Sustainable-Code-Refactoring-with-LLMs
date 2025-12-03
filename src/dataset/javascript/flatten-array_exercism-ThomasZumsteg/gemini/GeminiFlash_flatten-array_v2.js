class Flattener {
    flatten(array) {
        if (array == null) {
            return [];
        }

        if (!Array.isArray(array)) {
            return [array];
        }

        const result = [];
        for (const element of array) {
            if (Array.isArray(element)) {
                result.push(...this.flatten(element));
            } else {
                result.push(element);
            }
        }
        return result;
    }
}

module.exports = Flattener;