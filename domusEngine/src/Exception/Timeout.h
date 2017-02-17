//
// Created by paolo on 08/02/17.
//

#ifndef DOMUS_ENGINE_TIMEOUT_H
#define DOMUS_ENGINE_TIMEOUT_H

#include <exception>
#include <string>

class Timeout : public std::exception {
public:
    Timeout(const std::string & msg):message(msg) { }
    virtual ~Timeout() = default;

    virtual const char* what() const noexcept{
        return message.c_str();
    }

private:
    std::string message;
};

#endif //DOMUS_ENGINE_TIMEOUT_H
