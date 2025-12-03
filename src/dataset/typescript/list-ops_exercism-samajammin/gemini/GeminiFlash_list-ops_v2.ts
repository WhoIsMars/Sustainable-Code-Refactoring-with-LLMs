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
    this.values.push(...list.values);
    this._length = this.values.length;
    return this;
  }

  public concat(list: List<any>): List<any> {
    for (const item of list.values) {
      if (item instanceof List) {
        this.values.push(...item.values);
      } else {
        this.values.push(item);
      }
    }
    this._length = this.values.length;
    return this;
  }

  public filter(func: (value: T) => boolean): List<T> {
    const filteredValues: T[] = [];
    for (const value of this.values) {
      if (func(value)) {
        filteredValues.push(value);
      }
    }
    return new List(filteredValues);
  }

  public map<U>(func: (value: T) => U): List<U> {
    const mappedValues: U[] = [];
    for (const value of this.values) {
      mappedValues.push(func(value));
    }
    return new List(mappedValues);
  }

  public reverse(): List<T> {
    const reversedValues = [...this.values].reverse();
    return new List(reversedValues);
  }

  public foldl<U>(func: (acc: U, el: T) => U, initialVal: U): U {
    let acc:U = initialVal;
    for (const value of this.values) {
      acc = func(acc, value);
    }
    return acc;
  }

  public foldr<U>(func: (acc: U, el: T) => U, initialVal: U): U {
    let acc:U = initialVal;
    for (let i = this.values.length - 1; i >= 0; i--) {
      acc = func(acc, this.values[i]);
    }
    return acc;
  }
}