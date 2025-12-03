export default class List<T> {
  public values: T[];
  private _length: number;

  constructor(list: T[] = []) {
    this.values = [...list];
    this._length = list.length;
  }

  public length(): number {
    return this._length;
  }

  public push(value: T): List<T> {
    this.values[this._length++] = value;
    return this;
  }

  public unshift(value: T): List<T> {
    this.values = [value, ...this.values];
    this._length++;
    return this;
  }

  public append(list: List<T>): List<T> {
    this.values.push(...list.values);
    this._length += list._length;
    return this;
  }

  public concat(list: List<any>): List<any> {
    const listCopy = new List([...this.values]);
    listCopy.values.push(...list.values.flatMap((item: any) => (item.values ? item.values : [item])));
    listCopy._length = listCopy.values.length;
    return listCopy;
  }

  public filter(func: (value: T) => boolean): List<T> {
    const filteredValues = this.values.filter(func);
    return new List(filteredValues);
  }

  public map<U>(func: (value: T) => U): List<U> {
    const mappedValues = this.values.map(func);
    return new List(mappedValues);
  }

  public reverse(): List<T> {
    const reversedValues = [...this.values].reverse();
    return new List(reversedValues);
  }

  public foldl(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduce(func, initialVal);
  }

  public foldr(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduceRight(func, initialVal);
  }
}