class TwelveDays {
    private static readonly _numbers = [
        'first',
        'second',
        'third',
        'fourth',
        'fifth',
        'sixth',
        'seventh',
        'eighth',
        'ninth',
        'tenth',
        'eleventh',
        'twelfth',
    ];

    private static readonly _gifts = [
        'a Partridge in a Pear Tree.\n',
        'two Turtle Doves, ',
        'three French Hens, ',
        'four Calling Birds, ',
        'five Gold Rings, ',
        'six Geese-a-Laying, ',
        'seven Swans-a-Swimming, ',
        'eight Maids-a-Milking, ',
        'nine Ladies Dancing, ',
        'ten Lords-a-Leaping, ',
        'eleven Pipers Piping, ',
        'twelve Drummers Drumming, ',
    ];

    public static recite(fromVerse: number, toVerse: number): string {
        const verses: string[] = [];
        for (let i = fromVerse - 1; i < toVerse; i++) {
            const gifts = this._gifts
                .slice(0, i + 1)
                .reverse()
                .join('')
                .replace(/^and /, '');
            verses.push(`On the ${this._numbers[i]} day of Christmas my true love gave to me: ${gifts}`);
        }
        return verses.join('');
    }
}

export default TwelveDays;