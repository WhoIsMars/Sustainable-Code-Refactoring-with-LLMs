class TwelveDays {
    private static readonly _numbers: string[] = [
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

    private static readonly _gifts: string[] = [
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
        'twelve Drummers Drumming, '
    ];

    public static recite(fromVerse: number, toVerse: number): string {
        let song = '';
        for (let i = fromVerse - 1; i < toVerse; i++) {
            let verse = `On the ${TwelveDays._numbers[i]} day of Christmas my true love gave to me: `;
            let gifts = '';
            for (let j = i; j >= 0; j--) {
                gifts += (i > 0 && j === 0) ? 'and ' + TwelveDays._gifts[0] : TwelveDays._gifts[j];
            }
            verse += gifts;
            song += verse;
        }
        return song;
    }
}

export default TwelveDays