#include "invalidreturn.h"

InvalidReturn::InvalidReturn()
{

}

const char* InvalidReturn::what() const throw(){
    return "<invalid_return:expecting T >";
}
