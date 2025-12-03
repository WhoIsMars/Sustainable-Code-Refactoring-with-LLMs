class Scale(object):
    tones = (
        ('C,G,D,A,E,B,F#,a,e,b,f#,c#,g#,d#', 'C,C#,D,D#,E,F,F#,G,G#,A,A#,B'),
        ('A,F,Bb,Eb,Ab,Db,Gb,d,g,c,f,bb,eb', 'C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B'))
    stepsize = {'m': 1, 'M': 2, 'A': 3}
    
    # Pre-compute tonic lookup for O(1) access
    _tonic_lookup = {}
    for i, (tonics, tones) in enumerate(tones):
        tonic_list = tonics.split(',')
        tone_list = tones.split(',')
        for tonic in tonic_list:
            _tonic_lookup[tonic] = (tone_list, tonic_list.index(tonic))

    def __init__(self, tonic, intervals=None):
        if tonic not in self._tonic_lookup:
            raise ValueError("Not a recognized tonic {}".format(tonic))
        
        scale, tonic_idx = self._tonic_lookup[tonic]
        initial = t = scale.index(tonic[0].upper() + tonic[1:])
        scale_len = len(scale)
        
        self.pitches = []
        for i in intervals or 'mmmmmmmmmmmm':
            self.pitches.append(scale[t % scale_len])
            if scale_len < t - initial + self.stepsize[i] and i != 'A':
                raise ValueError("Cannot take that stepsize")
            t += self.stepsize[i]