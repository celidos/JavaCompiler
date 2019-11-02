#include <cctype>
#include <fstream>
#include <cassert>

#include "mc_driver.hpp"
#include "ast/handlers/expressions.hpp"
#include "ast/visitors/visitor_pretty_printer.hpp"

MC::MC_Driver::~MC_Driver() {
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
}

void MC::MC_Driver::parse(const char * const filename) {
    assert(filename != nullptr);
    std::ifstream in_file(filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }
    parse_helper(in_file);
}

void MC::MC_Driver::parse_helper(std::istream &stream) {
    PExpression root;

    delete(scanner);
    scanner = new MC::MC_Scanner(&stream);

    delete(parser);
    parser = new MC::MC_Parser(*scanner, *this, &root);
    const int accept = 0;
    if (parser->parse() != accept) {
        std::cerr << "Parsing failed!" << std::endl;
    } else {
        std::cerr << "Parsing OK" << std::endl;
    }
    ast::VisitorPrettyPrinter visit;
    root->accept(&visit);
}


void MC::MC_Driver::parse_tree(PExpression new_root) {

}