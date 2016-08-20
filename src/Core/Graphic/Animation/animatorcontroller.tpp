
template< typename T >
void AnimatorController::addParameter(std::string arg_name, T value){
    T* v = new T;
    *v = value;
    parameters[arg_name] = v;

}

template< typename T >
void AnimatorController::setParameter(std::string arg_name, T value ){
    parameters[arg_name] = &value;
}

template< typename T >
T AnimatorController::getParameter(std::string arg_name){
    auto it = parameters.find(arg_name);
    if( it != parameters.end() ){
        return *(T*)(it->second);
    }
}
