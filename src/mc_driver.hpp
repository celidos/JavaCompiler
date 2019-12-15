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

#include "ast/visitors/visitor_symbol_table_builder.hpp"
#include "ast/visitors/visitor_irt_builder.hpp"
#include "irt/visitors/visitor_graphviz.hpp"

namespace MC {

typedef std::shared_ptr<ast::Expression> PExpression;
typedef std::shared_ptr<ast::ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ast::ExpressionBinaryOp> PExpressionBinaryOp;

class MC_Driver{
public:
   MC_Driver() = default;

   virtual ~MC_Driver();

   // reading from file
   void parse(const char * input_filename,
              const char * ast_dot_output_filename,
              const char * irt_dot_output_filename);

   int __return_five() const { return 5; }
private:

   void parse_helper(std::istream &input_stream,
                     std::ofstream &ast_dot_output_stream,
                     std::ofstream &irt_dot_output_stream);
   MC::MC_Parser  *parser  = nullptr;
   MC::MC_Scanner *scanner = nullptr;
};

}
