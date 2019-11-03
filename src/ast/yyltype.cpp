//
// Created by celidos on 02.11.2019.
//

#include "yyltype.hpp"

namespace MC{

std::ostream & operator<<(std::ostream &os, const YYLTYPE &pos) {
    os << pos.first_line << ':' << pos.first_column << " - "
       << pos.last_line  << ':' << pos.last_column;
    return os;
}

}