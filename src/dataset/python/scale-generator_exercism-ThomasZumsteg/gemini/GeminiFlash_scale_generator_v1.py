class Scale(object):
    tones_data = {
        'sharps': (('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),),
        'flats': (('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'),)
    }
    stepsize = {'m': 1, 'M': 2, 'A': 3}

    def __init__(self, tonic, intervals=None):
        tonic_lower = tonic.lower()
        scale = None

        for key in self.tones_data:
            for tonics, tones in self.tones_data[key]:
                tonics_list = tonics.split(',')
                if tonic_lower in [t.lower() for t in tonics_list]:
                    scale = tones.split(',')
                    break
            if scale:
                break
        else:
            raise ValueError("Not a recognized tonic {}".format(tonic))

        initial = t = scale.index(tonic[0].upper() + tonic[1:])
        self.pitches = []
        interval_str = intervals or 'mmmmmmmmmmmm'
        scale_len = len(scale)

        for i in interval_str:
            self.pitches.append(scale[t % scale_len])
            step = self.stepsize[i]
            if scale_len < t - initial + step and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += step