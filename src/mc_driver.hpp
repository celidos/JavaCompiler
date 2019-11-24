#pragma once

#include <cassert>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <istream>
#include <string>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"
#include "ast/handlers/expressions.hpp"
#include "ast/handlers/statements.hpp"
#include "ast/visitors/visitor_pretty_printer.hpp"
#include "ast/visitors/visitor_graphviz.hpp"

namespace MC {

typedef std::shared_ptr<ast::Expression> PExpression;
typedef std::shared_ptr<ast::ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ast::ExpressionBinaryOp> PExpressionBinaryOp;

class MC_Driver{
public:
   MC_Driver() = default;

   virtual ~MC_Driver();

   // reading from file
   void parse(const char * const input_filename, const char * const output_filename);
private:

   void parse_helper(std::istream &i_stream, std::ofstream &o_stream);
   void parse_tree(PExpression new_root);
   MC::MC_Parser  *parser  = nullptr;
   MC::MC_Scanner *scanner = nullptr;
};

}
