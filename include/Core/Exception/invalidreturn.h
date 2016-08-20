#ifndef INVALIDRETURN_H
#define INVALIDRETURN_H

#include <exception>

class InvalidReturn
{
    public:
        InvalidReturn();

    public:
        virtual const char* what() const throw();
};
#endif // INVALIDRETURN_H
