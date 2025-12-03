export class ResistorColor {
  private static readonly colorConversion = new Map<string, number>([
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

  constructor(private readonly colors: string[]) {
    if (colors.length < 2) {
      throw new Error("At least two colors need to be present");
    }
  }

  value = (): number => {
    return (
      (ResistorColor.colorConversion.get(this.colors[0]) ?? 0) * 10 +
      (ResistorColor.colorConversion.get(this.colors[1]) ?? 0)
    );
  };
}