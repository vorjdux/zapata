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

// Generated by Flexc++ V1.08.00 on Sun, 29 Jun 2014 10:16:29 +0100

#ifndef zapataJSONLexerBASE_H_INCLUDED
#define zapataJSONLexerBASE_H_INCLUDED

#include <limits>
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include <memory>


// $insert namespace-open
namespace zapata
{

class JSONLexerBase
{
                // idx: rule, value: tail length (NO_INCREMENTS if no tail)
    typedef std::vector<int> VectorInt;

    enum        // RuleFlagsCount Indices, see s_rfc__[]
    {
        RULE = 0,
        FLAGS,
        ACCCOUNT,
    };

    enum
    {
        FINAL = 1,
        INCREMENT = 2,
        COUNT = 4,
        BOL = 8
    };

    enum 
    {
        AT_EOF = -1
    };

protected:
    enum Leave__
    {};

    enum class ActionType__
    {
        CONTINUE,               // transition succeeded, go on
        ECHO_CH,                // echo ch itself (d_matched empty)
        ECHO_FIRST,             // echo d_matched[0], push back the rest
        MATCH,                  // matched a rule
        RETURN,                 // no further continuation, lex returns 0.
    };

    enum class PostEnum__
    {
        END,                    // postCode called when lex__() ends 
        POP,                    // postCode called after switching files
        RETURN,                 // postCode called when lex__() returns
        WIP                     // postCode called when a non-returning rule
                                // was matched
    };

public:
    enum class StartCondition__ {
        // $insert startCondNames
        INITIAL,
        number,
        escaped,
        string_single,
        string,
        unicode
    };

private:
    struct FinData            // Info about intermediate matched rules while
    {                           // traversing the DFA
        size_t rule;
        size_t matchLen;
        size_t tailCount;
    };

    struct Final
    {
        FinData atBOL;
        FinData notAtBOL;
    };

        // class Input encapsulates all input operations. 
        // Its member get() returns the next input character
// $insert inputInterface
    class Input
    {
        std::deque<unsigned char> d_deque;  // pending input chars
        std::istream *d_in;                 // ptr for easy streamswitching
        size_t d_lineNr;                    // line count

        public:
            Input();
                                       // iStream: dynamically allocated
            Input(std::istream *iStream, size_t lineNr = 1);
            size_t get();                   // the next range
            void reRead(size_t ch);         // push back 'ch' (if < 0x100)
                                            // push back str from idx 'fmIdx'
            void reRead(std::string const &str, size_t fmIdx);
            size_t lineNr() const
            {
                return d_lineNr;
            }
            void close()                    // force closing the stream
            {
                delete d_in;
                d_in = 0;                   // switchStreams also closes
            }

        private:
            size_t next();                  // obtain the next character
    };

protected:

    struct StreamStruct
    {
        std::string pushedName;
        Input pushedInput;
    };

private:

    std::vector<StreamStruct>    d_streamStack;

    std::string     d_filename;             // name of the currently processed
    static size_t   s_istreamNr;            // file. With istreams it receives
                                            // the name "<istream #>", where
                                            // # is the sequence number of the 
                                            // istream (starting at 1)
    StartCondition__  d_startCondition;
    size_t          d_state;
    int             d_nextState;
    std::shared_ptr<std::ostream> d_out;
    bool            d_sawEOF;               // saw EOF: ignore tailCount
    bool            d_atBOL;                // the matched text starts at BOL
    std::vector<size_t> d_tailCount;         
    Final d_final;                          // 1st for BOL rules
                                            
                                            // only used interactively:
    std::istream *d_in;                     // points to the input stream
    std::shared_ptr<std::istringstream> d_line; // holds line fm d_in
    
    Input           d_input;
    std::string     d_matched;              // matched characters
    bool            d_return;               // return after a rule's action 
    bool            d_more = false;         // set to true by more()

protected:
    std::istream   *d_in__;
    int d_token__;                          // returned by lex__



    int     const (*d_dfaBase__)[48];

    static int     const s_dfa__[][48];
    static int     const (*s_dfaBase__[])[48];
    enum: bool { s_interactive__ = false };
    enum: size_t {
        s_rangeOfEOF__           = 45,
        s_finacIdx__             = 46,
        s_nRules__               = 24,
        s_maxSizeofStreamStack__ = 10
    };
    static size_t  const s_ranges__[];
    static size_t  const s_rfc__[][3];

public:
    JSONLexerBase(JSONLexerBase const &other)             = delete;
    JSONLexerBase &operator=(JSONLexerBase const &rhs)    = delete;

    bool                debug()     const;
    std::string const  &filename()  const;
    std::string const  &matched()   const;

    size_t              length()    const;
    size_t              lineNr()    const;

    void                setDebug(bool onOff);

    void                switchOstream(std::ostream &out);
    void                switchOstream(std::string const &outfilename);


    void                switchStreams(std::istream &in,
                                      std::ostream &out = std::cout);

    void                switchIstream(std::string const &infilename);
    void                switchStreams(std::string const &infilename,
                                      std::string const &outfilename);


// $insert interactiveDecl

protected:
    JSONLexerBase(std::istream &in, std::ostream &out);
    JSONLexerBase(std::string const &infilename, std::string const &outfilename);

    StartCondition__  startCondition() const;   // current start condition
    bool            popStream();
    std::ostream   &out();
    void            begin(StartCondition__ startCondition);
    void            echo() const;
    void            leave(int retValue) const;

//    `accept(n)' returns all but the first `n' characters of the current
// token back to the input stream, where they will be rescanned when the
// scanner looks for the next match.
//  So, it matches n of the characters in the input buffer, and so it accepts
//  n characters, rescanning the rest. 
    void            accept(size_t nChars = 0);      // former: less
    void            redo(size_t nChars = 0);        // rescan the last nChar
                                                    // characters, reducing
                                                    // length() by nChars
    void            more();
    void            push(size_t ch);                // push char to Input
    void            push(std::string const &txt);   // same: chars


    std::vector<StreamStruct> const &streamStack() const;

    void            pushStream(std::istream &curStream);
    void            pushStream(std::string const &curName);


    void            setFilename(std::string const &name);
    void            setMatched(std::string const &text);

    static std::string istreamName__();
        
        // members used by lex__(): they end in __ and should not be used
        // otherwise.

    ActionType__    actionType__(size_t range); // next action
    bool            return__();                 // 'return' from codeblock
    size_t          matched__(size_t ch);       // handles a matched rule
    size_t          getRange__(int ch);         // convert char to range
    size_t          get__();                    // next character
    size_t          state__() const;            // current state 
    void            continue__(int ch);         // handles a transition
    void            echoCh__(size_t ch);        // echoes ch, sets d_atBOL
    void            echoFirst__(size_t ch);     // handles unknown input
    void            inspectRFCs__();            // update d_tailCount
    void            noReturn__();               // d_return to false
    void            print__() const;            // optionally print token
    void            pushFront__(size_t ch);     // return char to Input
    void            reset__();                  // prepare for new cycle
                                                // next input stream:
    void            switchStream__(std::istream &in, size_t lineNr);   

private:
    void p_pushStream(std::string const &name, std::istream *streamPtr);
    void determineMatchedSize(FinData const &final);
    bool atFinalState();
};

inline std::ostream &JSONLexerBase::out()
{
    return *d_out;
}

inline void JSONLexerBase::push(size_t ch)
{
    d_input.reRead(ch);
}

inline void JSONLexerBase::push(std::string const &str)
{
    d_input.reRead(str, 0);
}

inline bool JSONLexerBase::atFinalState()
{
    return d_final.notAtBOL.rule != std::numeric_limits<size_t>::max() || 
            (d_atBOL && d_final.atBOL.rule != std::numeric_limits<size_t>::max());
}

inline void JSONLexerBase::setFilename(std::string const &name)
{
    d_filename = name;
}

inline void JSONLexerBase::setMatched(std::string const &text)
{
    d_matched = text;
}

inline std::string const &JSONLexerBase::matched() const
{
    return d_matched;
}

inline JSONLexerBase::StartCondition__ JSONLexerBase::startCondition() const
{
    return d_startCondition;
}

inline std::string const &JSONLexerBase::filename() const
{
    return d_filename;
}

inline void JSONLexerBase::echo() const
{
    *d_out << d_matched;
}

inline size_t JSONLexerBase::length() const
{
    return d_matched.size();
}

inline void JSONLexerBase::leave(int retValue) const
{
    throw static_cast<Leave__>(retValue);
}

inline size_t JSONLexerBase::lineNr() const
{
    return d_input.lineNr();
}

inline void JSONLexerBase::more()
{
    d_more = true;
}

inline void JSONLexerBase::begin(StartCondition__ startCondition)
{
    d_dfaBase__ = 
        s_dfaBase__[static_cast<int>(d_startCondition = startCondition)];
}

inline size_t JSONLexerBase::state__() const
{
    return d_state;
}

inline size_t JSONLexerBase::get__()
{
    return d_input.get();
}

inline bool JSONLexerBase::return__()
{
    return d_return;
}

inline void JSONLexerBase::noReturn__()
{
    d_return = false;
}

// $insert namespace-close
}

#endif //  JSONLexerBASE_H_INCLUDED




