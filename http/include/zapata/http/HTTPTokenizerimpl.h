// Generated by Bisonc++ V5.02.00 on Sat, 25 Mar 2017 16:02:37 +0000

// Include this file in the sources of the class HTTPTokenizer.

// $insert class.h
#include <zapata/http/HTTPTokenizer.h>
#include <zapata/exceptions/SyntaxErrorException.h>

// $insert namespace-open
namespace zpt {

inline void HTTPTokenizer::error(char const* msg) {
	// std::cerr << msg << '\n';
	throw zpt::SyntaxErrorException(string(msg));
}

// $insert lex
inline int HTTPTokenizer::lex() { return d_scanner.lex(); }

inline void HTTPTokenizer::print() {
	print__(); // displays tokens if --print was specified
}

inline void HTTPTokenizer::exceptionHandler__(std::exception const& exc) {
	throw; // re-implement to handle exceptions thrown by actions
}

// $insert namespace-close
}

// Add here includes that are only required for the compilation
// of HTTPTokenizer's sources.

// $insert namespace-use
// UN-comment the next using-declaration if you want to use
// symbols from the namespace zpt without specifying zpt::
// using namespace zpt;

// UN-comment the next using-declaration if you want to use
// int HTTPTokenizer's sources symbols from the namespace std without
// specifying std::

// using namespace std;
