export default class CircularBuffer<T> {
  private buffer: T[];
  private head: number;
  private tail: number;
  private count: number;
  readonly length: number;

  constructor(length: number) {
    this.buffer = new Array<T>(length);
    this.length = length;
    this.head = 0;
    this.tail = 0;
    this.count = 0;
  }

  isFull(): boolean {
    return this.count === this.length;
  }

  read(): T {
    if (this.count === 0) {
      throw BufferEmptyError;
    }
    const item = this.buffer[this.head];
    this.head = (this.head + 1) % this.length;
    this.count--;
    return item!;
  }

  write(item: T): void {
    if (this.isFull()) {
      throw BufferOverflowError;
    }
    this.buffer[this.tail] = item;
    this.tail = (this.tail + 1) % this.length;
    this.count++;
  }

  forceWrite(item: T): void {
    if (this.isFull()) {
      this.head = (this.head + 1) % this.length;
      this.count--;
    }
    this.buffer[this.tail] = item;
    this.tail = (this.tail + 1) % this.length;
    this.count++;
  }

  clear(): void {
    this.head = 0;
    this.tail = 0;
    this.count = 0;
  }
}

export const BufferOverflowError = 'Buffer overflowed';
export const BufferEmptyError = 'Buffer is empty';