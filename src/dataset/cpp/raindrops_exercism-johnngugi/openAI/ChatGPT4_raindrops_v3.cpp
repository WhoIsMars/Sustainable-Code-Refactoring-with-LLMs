#include "raindrops.h"
#include <string>

namespace raindrops
{
    const char* convert(int n)
    {
        static thread_local char buffer[12]; // Thread-local buffer for thread safety
        bool hasSound = false;
        int pos = 0;

        if (n % 3 == 0)
        {
            buffer[pos++] = 'P'; buffer[pos++] = 'l'; buffer[pos++] = 'i'; buffer[pos++] = 'n'; buffer[pos++] = 'g';
            hasSound = true;
        }

        if (n % 5 == 0)
        {
            buffer[pos++] = 'P'; buffer[pos++] = 'l'; buffer[pos++] = 'a'; buffer[pos++] = 'n'; buffer[pos++] = 'g';
            hasSound = true;
        }

        if (n % 7 == 0)
        {
            buffer[pos++] = 'P'; buffer[pos++] = 'l'; buffer[pos++] = 'o'; buffer[pos++] = 'n'; buffer[pos++] = 'g';
            hasSound = true;
        }

        if (!hasSound)
        {
            pos = snprintf(buffer, sizeof(buffer), "%d", n);
        }

        buffer[pos] = '\0'; // Null-terminate the string
        return buffer;
    }
}