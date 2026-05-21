#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

class Ini
{
private:
    std::ifstream fin_;

    std::string bd_host_;
    std::string bd_port_;
    std::string bd_name_;
    std::string bd_user_name_;
    std::string bd_user_password_;
    std::string startDir_;
    std::string extensions_;
public:
    Ini(const std::string &);

    std::string get_startDir();
    std::string get_bd_host();
    std::string get_bd_port();
    std::string get_bd_name();
    std::string get_bd_user_name();
    std::string get_bd_user_password();
    std::string get_extensions();
    ~Ini();
};
