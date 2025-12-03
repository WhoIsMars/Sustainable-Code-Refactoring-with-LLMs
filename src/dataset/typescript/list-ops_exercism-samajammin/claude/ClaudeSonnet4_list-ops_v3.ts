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
    this.values[this._length] = value;
    this._length++;
    return this;
  }

  public unshift(value: T): List<T> {
    this.values.unshift(value);
    this._length++;
    return this;
  }

  public append(list: List<T>): List<T> {
    this.values.push(...list.values);
    this._length += list._length;
    return this;
  }

  public concat(list: List<any>): List<any> {
    const result = new List(this.values);
    for (let i = 0; i < list.values.length; i++) {
      const item = list.values[i];
      if (item && typeof item === 'object' && 'values' in item) {
        result.values.push(...item.values);
        result._length += item.values.length;
      } else {
        result.values.push(item);
        result._length++;
      }
    }
    return result;
  }

  public filter(func: Function): List<{}> {
    const filtered = [];
    for (let i = 0; i < this._length; i++) {
      if (func(this.values[i])) {
        filtered.push(this.values[i]);
      }
    }
    const result = new List();
    result.values = filtered;
    result._length = filtered.length;
    return result;
  }

  public map(func: Function): List<{}> {
    const mapped = new Array(this._length);
    for (let i = 0; i < this._length; i++) {
      mapped[i] = func(this.values[i]);
    }
    const result = new List();
    result.values = mapped;
    result._length = this._length;
    return result;
  }

  public reverse(): List<{}> {
    const reversed = new Array(this._length);
    for (let i = 0; i < this._length; i++) {
      reversed[i] = this.values[this._length - 1 - i];
    }
    const result = new List();
    result.values = reversed;
    result._length = this._length;
    return result;
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