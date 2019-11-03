#include "mc_driver.hpp"

MC::MC_Driver::~MC_Driver() {
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
}

void MC::MC_Driver::parse(const char * const input_filename, const char * const output_filename) {
    assert(input_filename != nullptr);
    std::ifstream in_file(input_filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }

    assert(output_filename != nullptr);
    std::ofstream out_file(output_filename);
    if (!out_file.good()) {
        exit(EXIT_FAILURE);
    }

    parse_helper(in_file, out_file);
}

void MC::MC_Driver::parse_helper(std::istream &i_stream, std::ofstream &o_stream) {
    PExpression root;

    delete(scanner);
    scanner = new MC::MC_Scanner(&i_stream);

    delete(parser);
    parser = new MC::MC_Parser(*scanner, *this, &root);
    const int accept = 0;
    if (parser->parse() != accept) {
        std::cerr << "Parsing failed!" << std::endl;
    } else {
        std::cerr << "Parsing OK" << std::endl;
    }
    ast::VisitorPrettyPrinter visit_pretty_printer;
    root->accept(&visit_pretty_printer);

    ast::VisitorGraphviz visit_graphviz("my_graph");
    root->accept(&visit_graphviz);


    // TODO:: передавать путь до файла для текстового представления графа
    // std::ofstream outFile("output/graphviz_output.dot");
    // ./run_ast_graphviz.sh tests/samples/simple.java output/graphviz_output.dot output/output.svg

    Graphs::UndirectedGraphSerializer::serialize(visit_graphviz.GetGraph(), o_stream);
}


void MC::MC_Driver::parse_tree(PExpression new_root) {

}