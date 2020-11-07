#include <stdlib.h>

/**
 *  D. J. Bernstein hash function 
 **/
size_t djbHash(const char* cp) {
    size_t hash = 5381;
    while (*cp)
        hash = 33 * hash ^ (unsigned char) *cp++;
    return hash;
}
