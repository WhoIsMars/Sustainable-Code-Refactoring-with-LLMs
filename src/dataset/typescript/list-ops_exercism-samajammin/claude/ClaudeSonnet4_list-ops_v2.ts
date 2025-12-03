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
    for (const item of list.values) {
      if (item?.values) {
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
    const filteredValues = this.values.filter(func);
    const filteredList = new List();
    filteredList.values = filteredValues;
    filteredList._length = filteredValues.length;
    return filteredList;
  }

  public map(func: Function): List<{}> {
    const mappedValues = this.values.map(func);
    const mappedList = new List();
    mappedList.values = mappedValues;
    mappedList._length = mappedValues.length;
    return mappedList;
  }

  public reverse(): List<{}> {
    const reversed = new List();
    reversed.values = [...this.values].reverse();
    reversed._length = this._length;
    return reversed;
  }

  public foldl(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduce(func, initialVal);
  }

  public foldr(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduceRight(func, initialVal);
  }
}