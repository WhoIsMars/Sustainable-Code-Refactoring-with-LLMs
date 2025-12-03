class List {
    constructor(elements = []) {
        this.elements = elements;
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;

        if (listA.length === listB.length && this._isSublist(listA, listB)) {
            return "EQUAL";
        } else if (listB.length === 0) {
            return "SUPERLIST";
        } else if (listA.length === 0) {
            return "SUBLIST";
        } else if (listA.length > listB.length && this._isSublist(listA, listB)) {
            return "SUPERLIST";
        } else if (listB.length > listA.length && this._isSublist(listB, listA)) {
            return "SUBLIST";
        }
        return "UNEQUAL";
    }

    _isSublist(listA, listB) {
        const lenA = listA.length;
        const lenB = listB.length;

        for (let i = 0; i <= lenA - lenB; i++) {
            if (listA.slice(i, i + lenB).every((val, idx) => val === listB[idx])) {
                return true;
            }
        }
        return false;
    }
}

module.exports = List;