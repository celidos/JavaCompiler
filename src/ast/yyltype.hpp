//
// Created by celidos on 01.11.2019.
//

#ifndef JAVACOMPILER_SRC_AST_YYLTYPE_HPP_
#define JAVACOMPILER_SRC_AST_YYLTYPE_HPP_

#include <ostream>

namespace MC {

typedef struct YYLTYPE {
    unsigned int first_line;
    unsigned int first_column;
    unsigned int last_line;
    unsigned int last_column;
    friend std::ostream &operator<<(std::ostream &os, const YYLTYPE &dt);
} YYLTYPE;

std::ostream &operator<<(std::ostream &os, const YYLTYPE &dt);

}

#endif //JAVACOMPILER_SRC_AST_YYLTYPE_HPP_
