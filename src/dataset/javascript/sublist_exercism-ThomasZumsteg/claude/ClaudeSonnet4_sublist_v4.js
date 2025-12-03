class List {
    constructor(elements) {
        this.elements = elements || [];
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;
        const lenA = listA.length;
        const lenB = listB.length;

        if (lenA === lenB) {
            if (lenA === 0) return "EQUAL";
            for (let i = 0; i < lenA; i++) {
                if (listA[i] !== listB[i]) return "UNEQUAL";
            }
            return "EQUAL";
        }

        if (lenB === 0) return "SUPERLIST";
        if (lenA === 0) return "SUBLIST";

        const [longer, shorter] = lenA > lenB ? [listA, listB] : [listB, listA];
        const longerLen = longer.length;
        const shorterLen = shorter.length;

        for (let i = 0; i <= longerLen - shorterLen; i++) {
            let match = true;
            for (let j = 0; j < shorterLen; j++) {
                if (longer[i + j] !== shorter[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return lenA > lenB ? "SUPERLIST" : "SUBLIST";
            }
        }

        return "UNEQUAL";
    }
}

module.exports = List;