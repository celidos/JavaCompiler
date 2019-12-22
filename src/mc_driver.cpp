#include "mc_driver.hpp"


MC::MC_Driver::~MC_Driver() {
    delete (scanner);
    scanner = nullptr;
    delete (parser);
    parser = nullptr;
}

void MC::MC_Driver::parse(const char *const input_filename,
                          const char *const output_folder) {
    assert(input_filename != nullptr);
    std::ifstream in_file(input_filename);
    if (!in_file.good()) {
        exit(javacompiler::JC_EXIT_BAD_INPUT);
    }

    pipeline(in_file, std::string(output_folder));
}

void MC::MC_Driver::streamTree(const std::string& filename, const Graphs::UndirectedGraph& graph) {
    assert(filename != "");
    std::fstream out_file;
    out_file.open(filename, std::ios::out);
    if (!out_file.good()) {
        exit(javacompiler::JC_EXIT_BAD_INPUT);
    }
    Graphs::UndirectedGraphSerializer::serialize(graph, out_file);

    out_file.flush();
    out_file.close();
}

void MC::MC_Driver::pipeline(std::istream &input_stream,
                             const std::string &output_folder) {
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

    std::string green_text_start = "\033[32m";
    std::string green_text_end = "\033[0m";
    std::cerr << std::endl << green_text_start << "Running AST Graphviz..." << green_text_end << std::endl;
    ast::VisitorGraphviz visit_ast_graphviz("ast_graph");
    root->accept(&visit_ast_graphviz);

    std::cerr << green_text_start << "Running Symtable building..." << green_text_end << std::endl;
    ast::VisitorSymtableBuilder visit_build_symtable;
    root->accept(&visit_build_symtable);

    std::cerr << green_text_start << "Running Typechecker building..." << green_text_end << std::endl;
    ast::VisitorTypecheckerBuilder visit_build_typechecker(visit_build_symtable.getTable());
    root->accept(&visit_build_typechecker);

    if (!visit_build_typechecker.check_errors()) {
        exit(javacompiler::JC_EXIT_COMP_FAILURE_TYPEERR);
    }

    std::cerr << green_text_start << "Running IRT building..." << green_text_end << std::endl;
    ast::VisitorIrtBuilder visit_build_irt(visit_build_symtable.getTable());
    root->accept(&visit_build_irt);

    std::cerr << green_text_start << "Creating .dot AST files..." << green_text_end << std::endl;
    streamTree(output_folder + "/ast.dot",
               visit_ast_graphviz.GetGraph());

    std::cerr << green_text_start << "Creating .dot IRT files..." << green_text_end << std::endl;
    for (auto const& method : visit_build_irt.getIrtMethodTrees()) {
        std::cerr << green_text_start << "|   Serializing tree for " <<
             "'" << method.first << "'" << green_text_end << std::endl;
        irt::VisitorIrtGraphviz visit_irt_graphviz("irt_graph" + method.first);
        method.second->accept(&visit_irt_graphviz);

        streamTree(output_folder + "/irt" + "_" + method.first + ".dot",
                   visit_irt_graphviz.GetGraph());
    }


}
