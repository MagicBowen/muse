#include <iostream>
#include "antlr4-runtime.h"
#include "PromiseLexer.h"
#include "PromiseParser.h"
#include "PromiseVisitor.h"
#include "PromiseListener.h"

using namespace antlr4;

struct PromiseSyntaxVisitor : PromiseVisitor
{

};

int main(int argc, const char* argv[]) 
{
    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    PromiseLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    PromiseParser parser(&tokens);

    // Ref<tree::ParseTree> tree = parser.prog();
    // Ref<TreeShapeListener> listener(new TreeShapeListener());
    // tree::ParseTreeWalker::DEFAULT->walk(listener, tree);

    tree::ParseTree *tree = parser.prog();
    std::cout << tree->toStringTree(&parser) << std::endl;

    return 0;
}