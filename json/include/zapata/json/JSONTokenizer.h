// Generated by Bisonc++ V5.02.00 on Sat, 25 Mar 2017 15:53:50 +0000

#ifndef zptJSONTokenizer_h_included
#define zptJSONTokenizer_h_included

// $insert baseclass
#include "JSONTokenizerbase.h"
// $insert scanner.h
#include "JSONLexer.h"

// $insert namespace-open
namespace zpt {

#undef JSONTokenizer
class JSONTokenizer : public JSONTokenizerBase {
	// $insert scannerobject
	JScanner d_scanner;

      public:
	int parse();

      private:
	void error(char const* msg); // called on (syntax) errors
	int lex();		     // returns the next token from the
	// lexical scanner.
	void print(); // use, e.g., d_token, d_loc

	// support functions for parse():
	void executeAction(int ruleNr);
	void errorRecovery();
	int lookup(bool recovery);
	void nextToken();
	void print__();
	void exceptionHandler__(std::exception const& exc);
};

// $insert namespace-close
}

#endif
