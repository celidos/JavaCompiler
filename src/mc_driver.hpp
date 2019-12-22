#pragma once

#include <cassert>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <istream>
#include <string>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"
#include "errors.hpp"
#include "ast/handlers/expressions.hpp"
#include "ast/handlers/statements.hpp"
#include "ast/visitors/visitor_pretty_printer.hpp"
#include "ast/visitors/visitor_graphviz.hpp"

#include "ast/visitors/visitor_symbol_table_builder.hpp"
#include "ast/visitors/visitor_irt_builder.hpp"
#include "ast/visitors/visitor_typechecker.hpp"
#include "irt/visitors/visitor_graphviz.hpp"


namespace MC {

typedef std::shared_ptr<ast::Expression> PExpression;
typedef std::shared_ptr<ast::ExpressionInt> PExpressionInt;
typedef std::shared_ptr<ast::ExpressionBinaryOp> PExpressionBinaryOp;

class MC_Driver{
public:
    MC_Driver() = default;

    virtual ~MC_Driver();

    void parse(const char * input_filename,
               const char * output_folder);
private:
    void streamTree(const std::string& filename,
                    const Graphs::UndirectedGraph& graph);

    void pipeline(std::istream &input_stream,
                  const std::string &output_folder);
    MC::MC_Parser  *parser  = nullptr;
    MC::MC_Scanner *scanner = nullptr;
};

}
