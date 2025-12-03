class List {
    constructor(elements = []) {
        this.elements = elements;
    }

    compare(list) {
        const listA = this.elements;
        const listB = list.elements;

        if (listA.length === listB.length) {
            return this._isEqual(listA, listB) ? "EQUAL" : "UNEQUAL";
        }

        if (listB.length === 0) return "SUPERLIST";
        if (listA.length === 0) return "SUBLIST";

        const isSublist = listA.length > listB.length
            ? this._isSublist(listA, listB)
            : this._isSublist(listB, listA);

        if (isSublist) {
            return listA.length > listB.length ? "SUPERLIST" : "SUBLIST";
        }

        return "UNEQUAL";
    }

    _isEqual(listA, listB) {
        return listA.length === listB.length && listA.every((val, idx) => val === listB[idx]);
    }

    _isSublist(longer, shorter) {
        for (let i = 0; i <= longer.length - shorter.length; i++) {
            if (longer.slice(i, i + shorter.length).every((val, idx) => val === shorter[idx])) {
                return true;
            }
        }
        return false;
    }
}

module.exports = List;