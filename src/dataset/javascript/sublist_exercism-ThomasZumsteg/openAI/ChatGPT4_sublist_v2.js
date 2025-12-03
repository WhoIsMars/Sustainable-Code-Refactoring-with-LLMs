class List {
    constructor(elements = []) {
        this.elements = elements;
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;

        if (listA.length === listB.length) {
            return this.isEqual(listA, listB) ? "EQUAL" : "UNEQUAL";
        }

        if (listA.length < listB.length) {
            return this.isSublist(listA, listB) ? "SUBLIST" : "UNEQUAL";
        }

        return this.isSublist(listB, listA) ? "SUPERLIST" : "UNEQUAL";
    }

    isEqual(listA, listB) {
        return listA.length === listB.length && listA.every((val, idx) => val === listB[idx]);
    }

    isSublist(smaller, larger) {
        const smallerLength = smaller.length;
        if (smallerLength === 0) return true;

        for (let i = 0; i <= larger.length - smallerLength; i++) {
            if (larger.slice(i, i + smallerLength).every((val, idx) => val === smaller[idx])) {
                return true;
            }
        }
        return false;
    }
}

module.exports = List;