class Scale(object):
    _TONES_MAP = {
        tonic: tones.split(',')
        for tonics, tones in (
            ('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),
            ('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B')
        )
        for tonic in tonics.split(',')
    }
    _STEPSIZE = { 'm': 1, 'M': 2, 'A': 3 }
    _DEFAULT_INTERVALS = 'mmmmmmmmmmmm'

    def __init__(self, tonic, intervals=None):
        try:
            scale = self._TONES_MAP[tonic]
        except KeyError:
            raise ValueError("Not a recognized tonic {}".format(tonic)) from None

        tonic_letter = tonic[0].upper() + tonic[1:]
        try:
            initial = t = scale.index(tonic_letter)
        except ValueError:
            raise ValueError(f"Tonic {tonic} not found in scale") from None

        self.pitches = []
        intervals = intervals or self._DEFAULT_INTERVALS
        scale_len = len(scale)
        stepsize = self._STEPSIZE
        for i in intervals:
            self.pitches.append(scale[t % scale_len])
            step = stepsize[i]
            if scale_len < t - initial + step and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += step