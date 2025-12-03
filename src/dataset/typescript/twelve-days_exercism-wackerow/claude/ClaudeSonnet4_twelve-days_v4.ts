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

    public static recite(fromVerse: number, toVerse: number): string {
        const verses: string[] = []
        
        for (let i = fromVerse - 1; i < toVerse; i++) {
            const gifts: string[] = []
            
            for (let j = i; j >= 0; j--) {
                if (j === 0 && i > 0) {
                    gifts.push('and ' + this._gifts[0])
                } else {
                    gifts.push(this._gifts[j])
                }
            }
            
            verses.push(`On the ${this._numbers[i]} day of Christmas my true love gave to me: ${gifts.join('')}`)
        }
        
        return verses.join('')
    }
}

export default TwelveDays