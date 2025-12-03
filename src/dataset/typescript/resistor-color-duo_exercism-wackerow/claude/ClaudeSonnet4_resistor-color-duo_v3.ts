export class ResistorColor {
  private static readonly COLOR_VALUES = new Map([
    ["black", 0],
    ["brown", 1],
    ["red", 2],
    ["orange", 3],
    ["yellow", 4],
    ["green", 5],
    ["blue", 6],
    ["violet", 7],
    ["grey", 8],
    ["white", 9]
  ]);

  private firstColorValue: number;
  private secondColorValue: number;

  constructor(colors: string[]) {
    if (colors.length < 2) {
      throw "At least two colors need to be present";
    }
    
    this.firstColorValue = ResistorColor.COLOR_VALUES.get(colors[0]) ?? 0;
    this.secondColorValue = ResistorColor.COLOR_VALUES.get(colors[1]) ?? 0;
  }

  value = (): number => {
    return this.firstColorValue * 10 + this.secondColorValue;
  };
}