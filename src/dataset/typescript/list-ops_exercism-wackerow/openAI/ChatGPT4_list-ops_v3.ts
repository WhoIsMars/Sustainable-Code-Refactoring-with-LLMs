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
    const returnList = new List(this._values.slice());
    for (const item of list2.values) {
      if (item instanceof List) {
        returnList.append(item);
      } else {
        returnList.append(new List([item]));
      }
    }
    return returnList;
  }

  public filter(func: (arg0: T) => boolean): List<T> {
    return new List(this._values.filter(func));
  }

  public length(): number {
    return this._values.length;
  }

  public map(func: (arg0: T) => T): List<T> {
    return new List(this._values.map(func));
  }

  public foldl(func: (arg0: T, arg1: T) => T, start: T): T {
    return this._values.reduce(func, start);
  }

  public foldr(func: (arg0: T, arg1: T) => T, start: T): T {
    return this._values.reduceRight(func, start);
  }

  public reverse(): List<T> {
    return new List(this._values.slice().reverse());
  }
}