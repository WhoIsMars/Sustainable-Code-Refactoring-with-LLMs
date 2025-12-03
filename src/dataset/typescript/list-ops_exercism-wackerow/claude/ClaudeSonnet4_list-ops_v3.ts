export default class List<T> {
  private _values: T[];

  constructor(values?: T[]) {
      this._values = values ? values.slice() : [];
  }

  get values(): T[] {
    return this._values;
  }

  public append(list2: List<T>): List<T> {
    this._values.push(...list2._values);
    return this;
  }

  public concat(list2: List<any>): List<T> {
    const returnList = new List(this._values);
    const list2Values = list2._values;
    const length = list2Values.length;
    
    for (let i = 0; i < length; i++) {
      const item = list2Values[i];
      if (item && item.values) {
        returnList._values.push(...item.values);
      } else {
        returnList._values.push(item);
      }
    }
    return returnList;
  }

  public filter(func: (arg0: T) => boolean): List<T> {
    const filtered: T[] = [];
    const values = this._values;
    const length = values.length;
    
    for (let i = 0; i < length; i++) {
      if (func(values[i])) {
        filtered.push(values[i]);
      }
    }
    return new List(filtered);
  }
  
  public length(): number {
    return this._values.length;
  }
  
  public map(func: (arg0: T) => T): List<T> {
    const mapped: T[] = [];
    const values = this._values;
    const length = values.length;
    
    for (let i = 0; i < length; i++) {
      mapped.push(func(values[i]));
    }
    return new List(mapped);
  }
  
  public foldl(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    const values = this._values;
    const length = values.length;
    
    for (let i = 0; i < length; i++) {
      current = func(current, values[i]);
    }
    return current;
  }
  
  public foldr(func: (arg0: T, arg1: T) => T, start: T): T {
    let current = start;
    const values = this._values;
    
    for (let i = values.length - 1; i >= 0; i--) {
      current = func(current, values[i]);
    }
    return current;
  }
  
  public reverse(): List<T> {
    const reversed: T[] = [];
    const values = this._values;
    
    for (let i = values.length - 1; i >= 0; i--) {
      reversed.push(values[i]);
    }
    return new List(reversed);
  }
}