class Scale(object):
    _TONES_DATA = (
        ('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),
        ('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'))
    _STEPSIZE = {'m': 1, 'M': 2, 'A': 3}
    _TONICS_MAP = {}

    @classmethod
    def _initialize_tonics_map(cls):
        if not cls._TONICS_MAP:
            for tonics_str, tones_str in cls._TONES_DATA:
                tonics = tonics_str.split(',')
                tones = tones_str.split(',')
                for tonic in tonics:
                    cls._TONICS_MAP[tonic] = tones

    def __init__(self, tonic, intervals=None):
        Scale._initialize_tonics_map()
        
        tonic_key = tonic[0].upper() + tonic[1:]
        
        if tonic_key not in [t[0].upper() + t[1:] for t in sum([tonics.split(',') for tonics, _ in self._TONES_DATA], [])]:
            raise ValueError("Not a recognized tonic {}".format(tonic))

        scale = next((tones for tonics, tones in zip([tonics.split(',') for tonics, _ in self._TONES_DATA], [tones.split(',') for _, tones in self._TONES_DATA]) if tonic_key in [t[0].upper() + t[1:] for t in tonics]), None)

        if scale is None:
            raise ValueError("Not a recognized tonic {}".format(tonic))

        initial = t = scale.index(tonic_key)
        self.pitches = []
        intervals = intervals or 'mmmmmmmmmmmm'
        scale_len = len(scale)
        stepsize = self._STEPSIZE
        
        for i in intervals:
            self.pitches.append(scale[t % scale_len])
            step = stepsize[i]
            if scale_len < t - initial + step and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += step