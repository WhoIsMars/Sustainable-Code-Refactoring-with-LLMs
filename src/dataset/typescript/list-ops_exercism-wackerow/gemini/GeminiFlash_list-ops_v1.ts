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
      if (Array.isArray(item)) {
        returnList.append(new List<T>(item));
      } else {
        returnList.append(new List<T>([item]));
      }
    }
    return returnList;
  }

  public filter(func: (arg0: T) => boolean): List<T> {
    const filteredValues: T[] = [];
    for (let i = 0; i < this._values.length; i++) {
      if (func(this._values[i])) {
        filteredValues.push(this._values[i]);
      }
    }
    return new List<T>(filteredValues);
  }

  public length(): number {
    return this._values.length;
  }

  public map(func: (arg0: T) => T): List<T> {
    const mappedValues: T[] = new Array(this._values.length);
    for (let i = 0; i < this._values.length; i++) {
      mappedValues[i] = func(this._values[i]);
    }
    return new List<T>(mappedValues);
  }

  public foldl(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    for (let i = 0; i < this._values.length; i++) {
      current = func(current, this._values[i]);
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
    const reversedValues: T[] = new Array(this._values.length);
    for (let i = 0; i < this._values.length; i++) {
      reversedValues[i] = this._values[this._values.length - 1 - i];
    }
    return new List<T>(reversedValues);
  }
}