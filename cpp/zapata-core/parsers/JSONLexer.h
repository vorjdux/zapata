/*
    Author: Pedro (n@zgul) Figueiredo <pedro.figueiredo@gmail.com>
    Copyright (c) 2014 Pedro (n@zgul)Figueiredo
    This file is part of Zapata.

    Zapata is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zapata is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with Zapata.  If not, see <http://www.gnu.org/licenses/>.
*/

// Generated by Flexc++ V1.05.00 on Fri, 21 Mar 2014 16:37:56 +0000

#ifndef JSONLexer_H_INCLUDED_
#define JSONLexer_H_INCLUDED_

// $insert baseclass_h
#include "JSONLexerbase.h"

// $insert namespace-open
namespace zapata
{

// $insert classHead
class JSONLexer: public JSONLexerBase
{
    public:
        explicit JSONLexer(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        JSONLexer(std::string const &infile, std::string const &outfile);
        
        // $insert lexFunctionDecl
        int lex();

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts
        void postCode(zapata::JSONLexerBase::PostEnum__);     // re-implement this function for code that must
                            // be exec'ed before the patternmatching starts
};

// $insert scannerConstructors
inline JSONLexer::JSONLexer(std::istream &in, std::ostream &out)
:
    JSONLexerBase(in, out)
{}

inline JSONLexer::JSONLexer(std::string const &infile, std::string const &outfile)
:
    JSONLexerBase(infile, outfile)
{}

// $insert inlineLexFunction
inline int JSONLexer::lex()
{
    return lex__();
}

inline void JSONLexer::preCode() 
{
    // optionally replace by your own code
}

inline void JSONLexer::postCode(zapata::JSONLexerBase::PostEnum__ a)
{
    // optionally replace by your own code
}

inline void JSONLexer::print() 
{
    print__();
}

// $insert namespace-close
}

#endif // JSONLexer_H_INCLUDED_

