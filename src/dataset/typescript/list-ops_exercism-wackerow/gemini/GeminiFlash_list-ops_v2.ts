export default class List<T> {
  private _values: T[];

  constructor(values?: T[]) {
    this._values = values || [];
  }

  get values(): T[] {
    return this._values;
  }

  public append(list2: List<T>): List<T> {
    this._values.push(...list2.values);
    return this;
  }

  public concat(list2: List<any>): List<T> {
    const returnList = new List<T>(this.values.slice());
    for (const item of list2.values) {
      if (Array.isArray(item?.values)) {
        returnList.append(new List(item.values));
      } else {
        returnList.append(new List([item]));
      }
    }
    return returnList;
  }

  public filter(func: (arg0: T) => boolean): List<T> {
    const filteredValues: T[] = [];
    for (const value of this._values) {
      if (func(value)) {
        filteredValues.push(value);
      }
    }
    return new List<T>(filteredValues);
  }

  public length(): number {
    return this._values.length;
  }

  public map(func: (arg0: T) => T): List<T> {
    const mappedValues: T[] = [];
    for (const value of this._values) {
      mappedValues.push(func(value));
    }
    return new List<T>(mappedValues);
  }

  public foldl(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    for (const value of this._values) {
      current = func(current, value);
    }
    return current;
  }

  public foldr(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    for (let i = this._values.length - 1; i >= 0; i--) {
      current = func(current, this._values[i]);
    }
    return current;
  }

  public reverse(): List<T> {
    return new List<T>([...this._values].reverse());
  }
}