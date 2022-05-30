/*
** EPITECH PROJECT, 2021
** serialize_hpp
** File description:
** serialize_hpp
*/

#ifndef serialize
#define serialize
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdarg>
//#include <bits/stdc++.h>
#include <vector>
#include <string>

class Serialize {
    public:
        static void delete_line(const char *file_name, int n);
        virtual void pack() = 0;
        static bool isEmpty(std::string file);
    protected:
    private:
};

#endif /* !serialize_hpp */
