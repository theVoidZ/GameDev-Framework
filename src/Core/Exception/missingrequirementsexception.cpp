#include "missingrequirementsexception.h"

MissingRequirementsException::MissingRequirementsException(const char* target, const char* dependecies)
{
//    strcpy( targeted_class, target);
//    strcpy( dependencies_class, dependecies);
}

const char* MissingRequirementsException::what() const throw(){
    char* msg = new char[256];
    sprintf( msg, "<class: %s requires %s>", targeted_class, dependencies_class);
    return msg;
}

