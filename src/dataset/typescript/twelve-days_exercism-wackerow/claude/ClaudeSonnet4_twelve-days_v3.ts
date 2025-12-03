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
    ] as const

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
    ] as const

    private static readonly _verseCache = new Map<number, string>()

    private static _buildVerse(dayIndex: number): string {
        if (this._verseCache.has(dayIndex)) {
            return this._verseCache.get(dayIndex)!
        }

        const parts: string[] = [`On the ${this._numbers[dayIndex]} day of Christmas my true love gave to me: `]
        
        for (let j = dayIndex; j >= 0; j--) {
            if (dayIndex > 0 && j === 0) {
                parts.push('and ', this._gifts[0])
            } else {
                parts.push(this._gifts[j])
            }
        }

        const verse = parts.join('')
        this._verseCache.set(dayIndex, verse)
        return verse
    }

    public static recite(fromVerse: number, toVerse: number): string {
        const verses: string[] = []
        
        for (let i = fromVerse - 1; i < toVerse; i++) {
            verses.push(this._buildVerse(i))
        }
        
        return verses.join('')
    }
}

export default TwelveDays