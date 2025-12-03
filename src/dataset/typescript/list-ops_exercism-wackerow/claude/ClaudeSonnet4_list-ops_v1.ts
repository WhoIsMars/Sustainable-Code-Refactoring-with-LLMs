export default class List<T> {
  private _values: T[];

  constructor(values?: T[]) {
      this._values = values || [];
  }

  get values(): T[] {
    return this._values
  }

  public append(list2: List<T>): List<T> {
    this._values.push(...list2._values);
    return this;
  }

  public concat(list2: List<any>): List<T> {
    const returnList = new List([...this._values]);
    for (const item of list2._values) {
      if (item.values) {
        returnList._values.push(...item.values);
      } else {
        returnList._values.push(item);
      }
    }
    return returnList;
  }

  public filter(func: (arg0: T) => boolean): List<T> {
    const filtered: T[] = [];
    const len = this._values.length;
    for (let i = 0; i < len; i++) {
      if (func(this._values[i])) {
        filtered.push(this._values[i]);
      }
    }
    return new List(filtered);
  }
  
  public length(): number {
    return this._values.length;
  }
  
  public map(func: (arg0: T) => T): List<T> {
    const mapped: T[] = [];
    const len = this._values.length;
    for (let i = 0; i < len; i++) {
      mapped.push(func(this._values[i]));
    }
    return new List(mapped);
  }
  
  public foldl(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    const len = this._values.length;
    for (let i = 0; i < len; i++) {
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
    const reversed: T[] = [];
    for (let i = this._values.length - 1; i >= 0; i--) {
      reversed.push(this._values[i]);
    }
    return new List(reversed);
  }
}