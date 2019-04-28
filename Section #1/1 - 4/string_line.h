/**
 *  @file     string_line.h
 *  @authors  Mahmoud Ahmed(20160227) - Ahmad Khaled(20170377) - Mostafa Omar(20170292)
 *  @date     27/04/2019
 *  @version  1.0
 */
#pragma once

#ifndef STRINGLINE_H_INCLUDED
#define STRINGLINE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct stringLine
{
    string word;
    vector<int> line;

    // Overloading the comparison operators for tree insertion.
    bool operator<(const stringLine& rhs)
    {
        return word < rhs.word;
    }

    bool operator>(const stringLine& rhs)
    {
        return word > rhs.word;
    }

    bool operator==(const stringLine& rhs)
    {
        return word == rhs.word;
    }

    friend ostream& operator<<(ostream& out, const stringLine& strL)
    {
        out << strL.word << " ";
        for (unsigned int i = 0; i < strL.line.size(); ++i)
        {
            out << strL.line[i] << " ";
        }
        out << endl;
        return out;
    }
};

#endif // STRINGLINE_H_INCLUDED