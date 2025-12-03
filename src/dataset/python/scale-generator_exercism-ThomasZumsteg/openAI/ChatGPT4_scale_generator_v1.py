class Scale(object):
    tones = {
        'C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#': 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B',
        'A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb': 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'
    }
    stepsize = {'m': 1, 'M': 2, 'A': 3}

    def __init__(self, tonic, intervals=None):
        scale = None
        for tonics, tones in self.tones.items():
            if tonic in tonics.split(','):
                scale = tones.split(',')
                break
        if scale is None:
            raise ValueError(f"Not a recognized tonic {tonic}")
        
        tonic_formatted = tonic[0].upper() + tonic[1:]
        if tonic_formatted not in scale:
            raise ValueError(f"Invalid tonic format {tonic}")
        
        t = scale.index(tonic_formatted)
        self.pitches = []
        intervals = intervals or 'mmmmmmmmmmmm'
        for i in intervals:
            self.pitches.append(scale[t % len(scale)])
            t += self.stepsize[i]