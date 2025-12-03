export default class List<T> {
  public values: T[];
  private _length: number;

  constructor(list?: T[]) {
    this.values = list ? [...list] : [];
    this._length = this.values.length;
  }

  public length(): number {
    return this._length;
  }

  public push(value: T): List<T> {
    this.values.push(value);
    this._length++;
    return this;
  }

  public unshift(value: T): List<T> {
    this.values.unshift(value);
    this._length++;
    return this;
  }

  public append(list: List<T>): List<T> {
    if (list.values.length > 0) {
      this.values.push(...list.values);
      this._length += list.values.length;
    }
    return this;
  }

  public concat(list: List<any>): List<any> {
    const newList = new List([...this.values]);
    for (const item of list.values) {
      if (item instanceof List) {
        newList.values.push(...item.values);
      } else {
        newList.values.push(item);
      }
    }
    newList._length = newList.values.length;
    return newList;
  }

  public filter(func: (value: T) => boolean): List<T> {
    const filteredValues: T[] = [];
    for (const value of this.values) {
      if (func(value)) {
        filteredValues.push(value);
      }
    }
    const filteredList = new List(filteredValues);
    return filteredList;
  }

  public map<U>(func: (value: T) => U): List<U> {
    const mappedValues: U[] = [];
    for (const value of this.values) {
      mappedValues.push(func(value));
    }
    return new List<U>(mappedValues);
  }

  public reverse(): List<T> {
    const reversedValues = [...this.values].reverse();
    return new List<T>(reversedValues);
  }

  public foldl(func: (acc: T, el: T) => T, initialVal: T): T {
    let acc = initialVal;
    for (let i = 0; i < this._length; i++) {
      acc = func(acc, this.values[i]);
    }
    return acc;
  }

  public foldr(func: (acc: T, el: T) => T, initialVal: T): T {
    let acc = initialVal;
    for (let i = this._length - 1; i >= 0; i--) {
      acc = func(acc, this.values[i]);
    }
    return acc;
  }
}