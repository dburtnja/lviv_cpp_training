//
// Created by denys on 18.07.19.
//

#pragma once


#include <string>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

