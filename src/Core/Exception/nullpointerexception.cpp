#include "nullpointerexception.h"

NullPointerException::NullPointerException()
{

}

const char* NullPointerException::what() const throw(){
    char* msg = new char[256];
    sprintf( msg, "<nullptr: file=%s, function=%s, line=%d", __FILE__, __func__, __LINE__ );
    return msg;
}

