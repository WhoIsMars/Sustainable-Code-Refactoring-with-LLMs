class Scale(object):
    tones = {
        'C': ('C,C#,D,D#,E,F,F#,G,G#,A,A#,B', 'C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#'),
        'A': ('C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B', 'A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb')
    }
    stepsize = {'m': 1, 'M': 2, 'A': 3}

    def __init__(self, tonic, intervals=None):
        tonic_upper = tonic[0].upper() + tonic[1:]
        for scale_tones, tonics in self.tones.values():
            if tonic in tonics.split(','):
                scale = scale_tones.split(',')
                break
        else:
            raise ValueError(f"Not a recognized tonic {tonic}")

        self.pitches = []
        t = scale.index(tonic_upper)
        intervals = intervals or 'mmmmmmmmmmmm'
        scale_len = len(scale)

        for i in intervals:
            self.pitches.append(scale[t % scale_len])
            t += self.stepsize[i]
            if t - scale.index(tonic_upper) > scale_len and i != 'A':
                raise ValueError("Cannot take that stepsize")