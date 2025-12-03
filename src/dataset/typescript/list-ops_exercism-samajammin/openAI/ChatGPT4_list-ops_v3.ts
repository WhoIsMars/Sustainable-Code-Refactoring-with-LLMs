export default class List<T> {
  public values: T[];

  constructor(list: T[] = []) {
    this.values = [...list];
  }

  public length(): number {
    return this.values.length;
  }

  public push(value: T): List<T> {
    this.values.push(value);
    return this;
  }

  public unshift(value: T): List<T> {
    this.values = [value, ...this.values];
    return this;
  }

  public append(list: List<T>): List<T> {
    this.values.push(...list.values);
    return this;
  }

  public concat(list: List<any>): List<any> {
    const listCopy = new List([...this.values]);
    listCopy.values.push(...list.values.flatMap((item: any) => (item.values ? item.values : [item])));
    return listCopy;
  }

  public filter(func: (value: T) => boolean): List<T> {
    return new List(this.values.filter(func));
  }

  public map<U>(func: (value: T) => U): List<U> {
    return new List(this.values.map(func));
  }

  public reverse(): List<T> {
    return new List([...this.values].reverse());
  }

  public foldl(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduce(func, initialVal);
  }

  public foldr(func: (acc: T, el: T) => T, initialVal: T): T {
    return this.values.reduceRight(func, initialVal);
  }
}