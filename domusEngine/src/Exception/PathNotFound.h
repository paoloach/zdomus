//
// Created by paolo on 07/02/17.
//

#ifndef DOMUS_ENGINE_PATHNOTFOUND_H
#define DOMUS_ENGINE_PATHNOTFOUND_H

#include <exception>
#include <string>

class PathNotFound : public std::exception {
public:
    PathNotFound(const std::string & msg):message(msg) { }
    virtual ~PathNotFound() = default;

    virtual const char* what() const noexcept{
        return message.c_str();
    }

private:
    std::string message;
};


#endif //DOMUS_ENGINE_PATHNOTFOUND_H
