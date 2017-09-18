#ifndef _MDIMENSION_HPP_
#define _MDIMENSION_HPP_

#include <cstdlib>
#include "mdimension.hpp"

class mdimension{
    public:
        mdimension();
        mdimension(size_t Size);
        mdimension(size_t Row, size_t Col);
        mdimension(const mdimension & Dim);
        mdimension(const mdimension && Dim);

        void swap();

        size_t _Row;
        size_t _Col;
};

#endif