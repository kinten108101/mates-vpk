#include "maki/mkmath.h" // for maki_pow
#include "maki/mktype.h" // for unsigned short
#include <stdlib.h> // temporary i swear
#include <stdio.h> // temporary i swear

#define WLEN_MAX 10

unsigned short
kj_cstr2iarr (int* buffer,
               char delim,
               char* src)
{
    char* w = (char*)malloc(WLEN_MAX);
    char* const wlen_ptr = w; w++; // first byte is reserved for word length
    unsigned short buffer_len = 0;
    // TODO: buffer_len as buffer[0];
    while (1)
    {
        if (*src == delim || *src == '\0') {
            if ( *wlen_ptr > WLEN_MAX) exit(1);
            *buffer=0;
            buffer_len+=(unsigned short)*wlen_ptr;
            //w-=(*wlen_ptr);
            w = wlen_ptr;
            w++;
            while (*wlen_ptr != 0)
            {
                *buffer += (*w - '0') * maki_pow(10,(*wlen_ptr)-1);
                w++;
                (*wlen_ptr)--;
            }
            w = wlen_ptr;
            w++;
            if ( *src == '\0' ) break;
            else {
                src++;
                buffer++;
                continue;
            }
        }
        *w=*src;
        w++;src++;
        (*wlen_ptr)++;
    }
    return buffer_len;
}

// Problem with pascal string: buffer cant simply be created
// with malloc. 

void
kj_cstr2piarr (int* buff_ptr,
               char delim,
               char* cstr)
{
    unsigned short bufflen_tmp = 0;
    while (*cstr)
    {
        bufflen_tmp++;
        cstr++;
    }
    unsigned short* buff = (unsigned short)malloc(sizeof(unsigned short)*buff_len + 1);
    unsigned short* const bufflen_ptr = buff; buff++;
    *buff = bufflen_tmp;
    char* w = (char*)malloc(WLEN_MAX + 1);
    char* const wlen_ptr = w; w++;
    while (1)
    {
        if (*cstr == delim || *cstr == '\0') {
            if ( *wlen_ptr > WLEN_MAX) mkerr("A number exceeded max number of digits!");
            w = wlen_ptr;
            w++;
            *buffer=0;
            while (*wlen_ptr != 0)
            {
                *buff += (*w - '0') * maki_pow(10,(*wlen_ptr)-1);
                w++;
                (*wlen_ptr)--;
            }
            w = wlen_ptr;
            w++;
            if ( *cstr == '\0' ) break;
            else {
                cstr++;
                buffer++;
                continue;
            }
        }
        *w=*cstr;
        w++;cstr++;
        (*wlen_ptr)++;
    }
}

void
close_piarr