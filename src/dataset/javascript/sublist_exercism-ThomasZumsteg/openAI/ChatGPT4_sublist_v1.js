class List {
    constructor(elements = []) {
        this.elements = elements;
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;

        if (listA.length === listB.length) {
            return this._isSublist(listA, listB) ? "EQUAL" : "UNEQUAL";
        }

        if (listA.length > listB.length) {
            return this._isSublist(listA, listB) ? "SUPERLIST" : "UNEQUAL";
        }

        return this._isSublist(listB, listA) ? "SUBLIST" : "UNEQUAL";
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