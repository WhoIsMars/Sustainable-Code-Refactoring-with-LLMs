class Scale(object):
    _tonic_to_scale = {}
    _stepsize = {'m': 1, 'M': 2, 'A': 3}
    
    @classmethod
    def _initialize_tonic_mapping(cls):
        if cls._tonic_to_scale:
            return
        
        tones_data = (
            ('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),
            ('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B')
        )
        
        for tonics, tones in tones_data:
            scale = tones.split(',')
            for tonic in tonics.split(','):
                normalized_tonic = tonic[0].upper() + tonic[1:]
                try:
                    initial_index = scale.index(normalized_tonic)
                    cls._tonic_to_scale[tonic] = (scale, initial_index)
                except ValueError:
                    continue

    def __init__(self, tonic, intervals=None):
        self._initialize_tonic_mapping()
        
        if tonic not in self._tonic_to_scale:
            raise ValueError("Not a recognized tonic {}".format(tonic))
        
        scale, initial = self._tonic_to_scale[tonic]
        scale_len = len(scale)
        t = initial
        
        self.pitches = []
        for i in intervals or 'mmmmmmmmmmmm':
            self.pitches.append(scale[t % scale_len])
            step = self._stepsize[i]
            if scale_len < t - initial + step and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += step