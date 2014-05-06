// Generated by Bisonc++ V4.04.01 on Sat, 22 Mar 2014 14:40:39 +0000

#ifndef zapataJSONTokenizer_h_included
#define zapataJSONTokenizer_h_included

// $insert baseclass
#include "JSONTokenizerbase.h"
// $insert scanner.h
#include "JSONLexer.h"

// $insert namespace-open
namespace zapata
{

#undef JSONTokenizer
class JSONTokenizer: public JSONTokenizerBase
{
    // $insert scannerobject
    JScanner d_scanner;

    public:
        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner.
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
        void exceptionHandler__(std::exception const &exc);
};

// $insert namespace-close
}

#endif