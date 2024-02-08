#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../backend/auxiliary_modules.h"
#include <string>

class Controller {
public:
    Controller();

    void startParsing(const std::string &filename, Object &objInfo);
};

#endif // CONTROLLER_H
