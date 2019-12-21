#include "mc_driver.hpp"


MC::MC_Driver::~MC_Driver() {
    delete (scanner);
    scanner = nullptr;
    delete (parser);
    parser = nullptr;
}

void MC::MC_Driver::parse(const char *const input_filename,
                          const char *const ast_dot_output_filename,
                          const char *const irt_dot_output_filename) {
    assert(input_filename != nullptr);
    std::ifstream in_file(input_filename);
    if (!in_file.good()) {
        exit(javacompiler::JC_EXIT_BAD_INPUT);
    }

    assert(ast_dot_output_filename != nullptr);
    std::ofstream ast_out_file(ast_dot_output_filename);
    if (!ast_out_file.good()) {
        exit(javacompiler::JC_EXIT_BAD_INPUT);
    }

    assert(irt_dot_output_filename != nullptr);
    std::ofstream irt_out_file(irt_dot_output_filename);
    if (!irt_out_file.good()) {
        exit(javacompiler::JC_EXIT_BAD_INPUT);
    }

    parse_helper(in_file, ast_out_file, irt_out_file);
}

void MC::MC_Driver::parse_helper(std::istream &input_stream,
                                 std::ofstream &ast_dot_output_stream,
                                 std::ofstream &irt_dot_output_stream) {
    ast::PGoal root;

    std::cerr << std::endl;

    delete (scanner);
    scanner = new MC::MC_Scanner(&input_stream);

    delete (parser);
    parser = new MC::MC_Parser(*scanner, *this, &root);
    const int accept = 0;
    if (parser->parse() != accept) {
        std::cerr << "Parsing failed!" << std::endl;
        exit(javacompiler::JC_EXIT_COMP_FAILURE_SYNTERR);
    } else {
        std::cerr << "Parsing OK" << std::endl;
    }

    // TODO: разбить на более мелкие функции, это уже не просто парсинг, тут вообще
    // весь пайплайн

    //std::cerr << "Running PrettyPrinter..." << std::endl;
    //ast::VisitorPrettyPrinter visit_pretty_printer;
    //root->accept(&visit_pretty_printer);

    std::cerr << std::endl << "Running AST Graphviz..." << std::endl;
    ast::VisitorGraphviz visit_ast_graphviz("ast_graph");
    root->accept(&visit_ast_graphviz);

    std::cerr << "Running Symtable building..." << std::endl;
    ast::VisitorSymtableBuilder visit_build_symtable;
    root->accept(&visit_build_symtable);

//    std::cerr << "Running Typechecker building..." << std::endl;
//    ast::VisitorTypecheckerBuilder visit_build_typechecker(visit_build_symtable.getTable());
//    root->accept(&visit_build_typechecker);

//    if (!visit_build_typechecker.check_errors()) {
//        exit(javacompiler::JC_EXIT_COMP_FAILURE_TYPEERR);
//    }

    std::cerr << "Running IRT building..." << std::endl;
    ast::VisitorIrtBuilder visit_build_irt(visit_build_symtable.getTable());
    root->accept(&visit_build_irt);

    std::cerr << "Running IRT Graphviz..." << std::endl;
    irt::VisitorIrtGraphviz visit_irt_graphviz("irt_graph");
//    visit_build_irt.retrieveIrt()->accept(&visit_irt_graphviz);

    // TODO сделать разные файлы для вывода, выводить в цикле
    auto irt_method_trees = visit_build_irt.getIrtMethodTrees();
    irt_method_trees["main"]->accept(&visit_irt_graphviz);

    std::cerr << "Serializing AST..." << std::endl;
    Graphs::UndirectedGraphSerializer::serialize(visit_ast_graphviz.GetGraph(),
                                                 ast_dot_output_stream);

    std::cerr << "Serializing IRT..." << std::endl;
    Graphs::UndirectedGraphSerializer::serialize(visit_irt_graphviz.GetGraph(),
                                                 irt_dot_output_stream);
}
