class Scale(object):
    tones = {
        'C': (('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'), 0),
        'A': (('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'), 1)
    }
    stepsize = { 'm': 1, 'M': 2, 'A': 3 }

    def __init__(self, tonic, intervals=None):
        tonic_key = tonic[0].upper()
        if len(tonic) > 1:
            tonic_key += tonic[1:]

        found = False
        scale_data = None

        for key, (tonics_str, tones_str) in self.tones.items():
            if tonic_key[0] == key:
                tonics = tonics_str.split(',')
                if tonic_key in tonics:
                    scale_data = (tones_str.split(','), tonics.index(tonic_key))
                    found = True
                    break

        if not found:
            raise ValueError("Not a recognized tonic {}".format(tonic))

        scale, initial = scale_data
        self.pitches = []
        t = initial
        for i in intervals or 'mmmmmmmmmmmm':
            self.pitches.append(scale[t % len(scale)])
            step = self.stepsize[i]
            if t + step - initial > len(scale) and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += step