export class ResistorColor {
  private static readonly colorConversion: Record<string, number> = {
    black: 0,
    brown: 1,
    red: 2,
    orange: 3,
    yellow: 4,
    green: 5,
    blue: 6,
    violet: 7,
    grey: 8,
    white: 9,
  };

  constructor(private readonly colors: [string, string]) {
    if (colors.length < 2) {
      throw new Error("At least two colors need to be present");
    }
  }

  value(): number {
    const [first, second] = this.colors;
    return ResistorColor.colorConversion[first] * 10 + ResistorColor.colorConversion[second];
  }
}