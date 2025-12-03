class Scale(object):
    _tones = (
        ('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),
        ('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'))
    _stepsize = {'m': 1, 'M': 2, 'A': 3}
    _tonic_to_scale = {}
    
    @classmethod
    def _build_tonic_map(cls):
        if not cls._tonic_to_scale:
            for tonics, tones in cls._tones:
                tones_list = tones.split(',')
                for tonic in tonics.split(','):
                    cls._tonic_to_scale[tonic] = tones_list

    def __init__(self, tonic, intervals=None):
        self._build_tonic_map()
        
        scale = self._tonic_to_scale.get(tonic)
        if scale is None:
            raise ValueError("Not a recognized tonic {}".format(tonic))
        
        normalized_tonic = tonic[0].upper() + tonic[1:]
        initial = t = scale.index(normalized_tonic)
        scale_len = len(scale)
        intervals = intervals or 'mmmmmmmmmmmm'
        
        self.pitches = []
        for i in intervals:
            self.pitches.append(scale[t % scale_len])
            step = self._stepsize[i]
            if i != 'A' and scale_len < t - initial + step:
                raise ValueError("Cannot take that stepsize")
            t += step