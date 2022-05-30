/*
** EPITECH PROJECT, 2021
** serialized_
** File description:
** serialize_cpp
*/

#include "Serialize.hpp"

void Serialize::delete_line(const char *file_name, int n)
{
    std::ifstream input(file_name);
    std::ofstream tmp("temp", std::ofstream::out);
    if (tmp.is_open()) {
        int line_no = 0;
        std::string line;
        while(getline(input, line)) {
            if (n != line_no)
                tmp << line + "\n";
            line_no++;
        }
        tmp.close();
        input.close();
    }
    if (remove(file_name) != 0)
        std::cerr << "Error deleting file" << std::endl;
    if (rename("temp", file_name) != 0)
        std::cerr << "Error rename file" << std::endl;
}

bool Serialize::isEmpty(std::string file) {
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open(file);
    std::string line;
    getline(myfile, line);

    if (line.empty()) {
        myfile.close();
        return true;
    }
    myfile.close();
    return false;
}

