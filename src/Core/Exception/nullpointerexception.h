#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class NullPointerException
{
    public:
        NullPointerException();

    public:
        virtual const char* what() const throw();
};

#endif // NULLPOINTEREXCEPTION_H
