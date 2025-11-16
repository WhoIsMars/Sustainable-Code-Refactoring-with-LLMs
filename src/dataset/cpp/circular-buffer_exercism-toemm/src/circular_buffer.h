#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdexcept>

namespace circular_buffer {

template<typename T>
class circular_buffer {

    public: 
    circular_buffer(int size) {
        _buffer = new T[size]();

        _writeptr = _buffer;
        _beginptr = _buffer;

        _readptr = nullptr;
        _endptr = _beginptr + size;
    }

    
    ~circular_buffer() {
        delete[] _buffer;

    }
 
    T read() {
        if (_readptr == nullptr) 
            throw std::domain_error("No values written.");
       
        auto read_val = *_readptr++; 

        // loop read_ptr back to begining if at end
        if (_readptr == _endptr) _readptr = _beginptr;

        // if read catches up to write, there is nothing to read anymore
        if (_readptr == _writeptr) _readptr = nullptr;

        return read_val;
        
    }

    void write(T val) {
        // if write catches up with read, then array has to be full
        if (_readptr == _writeptr) throw std::domain_error("Array is full.");

        // first write, init readptr or if read catches up to write
        if (_readptr == nullptr) _readptr = _writeptr;

        // write, and advance writeptr
        *_writeptr++ = val;

        // end of array reached, loop to begining
        if (_writeptr == _endptr) _writeptr = _beginptr;
    }

    void overwrite(T val) {
        
        // if read is not write, then array isn't full
        if (_readptr != _writeptr) write(val);
        else {

            _readptr++;
            *_writeptr++ = val;

            // loop around
            if (_readptr == _endptr) _readptr = _beginptr;
            if (_writeptr == _endptr) _writeptr = _beginptr;
        }

    }

    void clear() {
        _readptr = nullptr;
    }

    private:
    T* _buffer;
    T* _readptr;
    T* _writeptr;
    T* _beginptr;
    T* _endptr;

};


}  // namespace circular_buffer

#endif  // CIRCULAR_BUFFER_H

