class List {
    constructor(elements) {
        this.elements = elements || [];
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;
        const lenA = listA.length;
        const lenB = listB.length;

        // Early return for equal length arrays
        if (lenA === lenB) {
            for (let i = 0; i < lenA; i++) {
                if (listA[i] !== listB[i]) {
                    return "UNEQUAL";
                }
            }
            return "EQUAL";
        }

        // Early return for empty arrays
        if (lenB === 0) return "SUPERLIST";
        if (lenA === 0) return "SUBLIST";

        // Determine which is longer and check containment
        const [longer, shorter, isSwapped] = lenA > lenB ? 
            [listA, listB, false] : [listB, listA, true];

        const maxStart = longer.length - shorter.length;
        
        outer: for (let i = 0; i <= maxStart; i++) {
            for (let j = 0; j < shorter.length; j++) {
                if (longer[i + j] !== shorter[j]) {
                    continue outer;
                }
            }
            return isSwapped ? "SUBLIST" : "SUPERLIST";
        }

        return "UNEQUAL";
    }
}

module.exports = List;