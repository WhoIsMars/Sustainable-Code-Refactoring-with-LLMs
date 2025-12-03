export class ResistorColor {
  private colors: string[];

  private static colorConversion: { [i: string]: number } = {
    "black": 0,
    "brown": 1,
    "red": 2,
    "orange": 3,
    "yellow": 4,
    "green": 5,
    "blue": 6,
    "violet": 7,
    "grey": 8,
    "white": 9
  };

  constructor(colors: string[]) {
    if (colors.length < 2) {
      throw "At least two colors need to be present";
    }
    this.colors = colors;
  }

  value = (): number => {
    const color1 = this.colors[0];
    const color2 = this.colors[1];

    return ResistorColor.colorConversion[color1] * 10 + ResistorColor.colorConversion[color2];
  };
}