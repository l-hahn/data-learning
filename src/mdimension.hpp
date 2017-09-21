#ifndef _MDIMENSION_HPP_
#define _MDIMENSION_HPP_

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "mdimension.hpp"

class mdimension{
    public:
        mdimension();
        mdimension(size_t Size);
        mdimension(size_t Row, size_t Col);
        mdimension(const mdimension & Dim);
        mdimension(const mdimension && Dim);

        std::string to_string() const;
        bool empty() const;
        void swap();

        bool operator==(const mdimension && Dim) const;
        bool operator!=(const mdimension && Dim) const;
        bool operator==(const mdimension & Dim) const;
        bool operator!=(const mdimension & Dim) const;

        mdimension& operator=(const mdimension && Dim);
        mdimension& operator=(const mdimension & Dim);

        mdimension operator*(const mdimension && DimL) const;
        mdimension& operator*=(const mdimension && DimL);
        mdimension operator*(const mdimension & DimL) const;
        mdimension& operator*=(const mdimension & DimL);

        // size(Mat) == _Row x _Col
        size_t _Row;
        size_t _Col;
};

#endif