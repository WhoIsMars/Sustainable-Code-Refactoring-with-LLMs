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
    ]

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
        'twelve Drummers Drumming, '
    ]

    private static readonly _verses: string[] = (() => {
        const verses: string[] = []
        for (let i = 0; i < 12; i++) {
            let verse = `On the ${TwelveDays._numbers[i]} day of Christmas my true love gave to me: `
            
            for (let j = i; j >= 0; j--) {
                if (i > 0) {
                    verse += j > 0 ? TwelveDays._gifts[j] : 'and ' + TwelveDays._gifts[0]
                } else {
                    verse += TwelveDays._gifts[0]
                }
            }
            verses[i] = verse
        }
        return verses
    })()

    public static recite(fromVerse: number, toVerse: number): string {
        const verses: string[] = []
        for (let i = fromVerse - 1; i < toVerse; i++) {
            verses.push(this._verses[i])
        }
        return verses.join('')
    }
}

export default TwelveDays