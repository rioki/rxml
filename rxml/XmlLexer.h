
#ifndef _XML_LEXER_H_
#define _XML_LEXER_H_

#if ! defined(_SKIP_YYFLEXLEXER_)
#include "FlexLexer.h"
#endif

#include <iosfwd>
#include "XmlParser.hpp"

class XmlLexer : public yyFlexLexer
{
public:
    typedef rxml::parser::token token;
    typedef rxml::parser::token_type token_type;
    typedef rxml::parser::semantic_type semantic_type;
    typedef rxml::parser::location_type location_type;

    XmlLexer(std::istream& input, std::ostream& error);    
        
    int lex(semantic_type* yylval, location_type* yylloc);
    
    virtual int yylex();
            
private:
    semantic_type* yylval;
    location_type* yylloc;                
    
    std::ostream& error;
    
    XmlLexer(const XmlLexer&);
    const XmlLexer& operator = (const XmlLexer&);
};

#endif