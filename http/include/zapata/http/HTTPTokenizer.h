// Generated by Bisonc++ V5.02.00 on Sat, 25 Mar 2017 16:02:37 +0000

#ifndef zptHTTPTokenizer_h_included
#define zptHTTPTokenizer_h_included

// $insert baseclass
#include <zapata/http/HTTPTokenizerbase.h>
// $insert scanner.h
#include <zapata/http/HTTPLexer.h>

// $insert namespace-open
namespace zpt {

#undef HTTPTokenizer
class HTTPTokenizer : public HTTPTokenizerBase {
	// $insert scannerobject
	Scanner d_scanner;

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
