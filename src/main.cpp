#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "global.hpp"
#include "yaccer.hpp"

// Included to test:
#include "expression.hpp"
#include "code-generator.hpp"
#include "code-visitor.hpp"
#include "operator.hpp"
#include "statement.hpp"
#include "type.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::exit;
using std::fopen;
using std::system;
using std::ofstream;

// void test() {

//     {
//         cout << "Test 1:\n/* 42+(-(a+b+c-d)) */\n\n";
//         IdExpression* ida = new IdExpression("a");
//         IdExpression* idb = new IdExpression("b");
//         IdExpression* idc = new IdExpression("c");
//         IdExpression* idd = new IdExpression("d");
//         BinExpression* binopAB = new BinExpression(ida, idb, OP_PLUS);
//         BinExpression* binopABC = new BinExpression(binopAB, idc, OP_PLUS);
//         BinExpression* binopABCD = new BinExpression(binopABC, idd, OP_PLUS);
//         UnExpression* binopABCDminus = new UnExpression(binopABCD, OP_UN_MINUS);
//         ParenExpression* paren = new ParenExpression(binopABCDminus);
//         AtomExpValue aev;
//         aev.intval = 42;
//         AtomExpression* fortytwo = new AtomExpression(aev, MkTypeInt());
//         BinExpression* fortytwoPlusParen = new BinExpression(fortytwo, paren, OP_PLUS);

//         CodeVisitor visitor;
//         std::cout << visitor.visit(fortytwoPlusParen) << "\n\n";
//     }

//     {
//         cout << "Test 2:\n/* int c = a+b */\n\n";
//         IdExpression a("a");
//         IdExpression b("b");
//         BinExpression bin(&a,&b,OP_PLUS);
//         VarDec c(MkTypeInt(), "c", &bin);
//         CodeVisitor vis;
//         vis.visit(&c);
//     }
// }

void generateWholeCode(ofstream &out){
    CodeGenerator cg = CodeGenerator(program, out);
    cg.generateCode();
}

void printHelp() {
    cout << "mjv inputFile [-o outputFile]" << endl;
    cout << "inputFile:" << endl << "\tFile to be compiled." << endl;
    cout << "outputFile:" << endl << "\tGenerated output program." << endl;
}

void checkArgs(int argc, char const *argv[], string &outFile, string& inFile) {
    bool flag_o = false;
    bool flag_input = false;

    for (int i = 1; i < argc; ++i) {
        if(string(argv[i]) == "-o") {
            if(flag_o) {
                cerr << "Flag \"-o\" is specified more than once!" << endl;
            }

            if(i+1 >= argc) {
                cerr << "Flag \"-o\" is specified without filename argument!" << endl;
                cerr << "See \"mjv -h\"" << endl;
                exit(-1);
            }
            else
                outFile = string(argv[++i]);

            flag_o = true;
        }
        else if(string(argv[i]) == "-h") {
            printHelp();
            exit(0);
        }
        else {
            if(!flag_input) {
                inFile = string(argv[i]);
                flag_input = true;
            }
            else {
                cerr << "Input file is specified more than once!" << endl;
                cerr << "See \"mjv -h\"" << endl;
                exit(-1);
            }
        }
    }

    if(!flag_o)
        outFile = "a.out";

    if(!flag_input) {
        cerr << "Input file not specified!" << endl;
        cerr << "See \"mjv -h\"" << endl;
        exit(-1);
    }
}

void openInput(string& inFile) {
    extern FILE *yyin;
    yyin = fopen(inFile.c_str(), "r");

    if(yyin == nullptr) {
        cerr << inFile << " cannot be openned!" << endl;
        exit(-1); 
    }
}

int main(int argc, char const *argv[]) {
    string outFile;
    string inFile;
    
    checkArgs(argc, argv, outFile, inFile);

    openInput(inFile);

    string gen_infile = inFile.substr(inFile.find_last_of('/')+1) + ".cpp";
    ofstream out(gen_infile);
    if(yyparse() != 1){
        // program->print();
        auto pool = buildClassSymtablePool(program);

        if(pool != nullptr) {
            generateWholeCode(out);
            // system("g++ -Wall -std=c++11 ./src/code-generator/value.cpp -c -o value.o");
            // system("g++ -Wall -std=c++11 ./src/code-generator/activation-record.cpp -c -o activation-record.o");
            // system(string("g++ -std=c++11 -I src/code-generator/ value.o activation-record.o " + gen_infile + " -o " + outFile).c_str());
            // system(string("rm value.o activation-record.o " + gen_infile).c_str());
        }
    }

    return 0;
}
