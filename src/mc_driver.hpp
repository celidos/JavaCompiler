#pragma once

#include <string>
#include <cstddef>
#include <istream>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"

namespace MC {

typedef std::shared_ptr<ast::Expression> PExpression;
typedef std::shared_ptr<ast::ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ast::ExpressionBinaryOp> PExpressionBinaryOp;

class MC_Driver{
public:
   MC_Driver() = default;

   virtual ~MC_Driver();

   // reading from file
   void parse(const char * const filename);
private:

   void parse_helper(std::istream &stream);
   void parse_tree(PExpression new_root);
   MC::MC_Parser  *parser  = nullptr;
   MC::MC_Scanner *scanner = nullptr;
};

}
