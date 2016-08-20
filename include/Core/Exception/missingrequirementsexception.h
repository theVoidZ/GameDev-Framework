#ifndef MISSINGREQUIREMENTSEXCEPTION_H
#define MISSINGREQUIREMENTSEXCEPTION_H

#include <string>

class MissingRequirementsException
{
    public:
        MissingRequirementsException(const char *target, const char *dependecies);
        virtual const char* what() const throw();

    protected:
        const char* targeted_class;
        const char* dependencies_class;
};

#endif // MISSINGREQUIREMENTSEXCEPTION_H
