#include <iostream>
#include <string>
#include <set>
#include <exception>
#include "antlr4-runtime.h"
#include "PromiseLexer.h"
#include "PromiseParser.h"
#include "PromiseBaseVisitor.h"

using namespace antlr4;

struct PromiseSyntaxVisitor : PromiseBaseVisitor
{
private:
    antlrcpp::Any visitFactdef(PromiseParser::FactdefContext *context) override
    {
        auto id = context->ID()->getText();
        if(isExisted(id)) throw "Error: duplicate fact id " + id;
        factIdTable.insert(id);
        return 1;
    }

    antlrcpp::Any visitFactId(PromiseParser::FactIdContext *context) override
    {
        return checkFactIdDefined(*context);
    }

    antlrcpp::Any visitClosureFactId(PromiseParser::ClosureFactIdContext *context) override
    {
        return checkFactIdDefined(*context);
    }

private:
    bool isExisted(const std::string& id) const
    {
        return !(factIdTable.find(id) == factIdTable.end());
    }

    template<typename CONTEXT>
    antlrcpp::Any checkFactIdDefined(CONTEXT& ctxt)
    {
        auto id = ctxt.ID()->getText();
        if(!isExisted(id)) throw "Error: missing fact " + id;
        return 0;
    }

private:
    std::set<std::string> factIdTable;
};

int main(int argc, const char* argv[]) 
{
    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    PromiseLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    PromiseParser parser(&tokens);

    tree::ParseTree *tree = parser.prog();
    PromiseSyntaxVisitor visitor;
    visitor.visit(tree);

    std::cout << "parse ok!\n";
    return 0;
}
