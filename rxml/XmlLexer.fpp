
%option c++
%option 8bit
%option warn
%option yyclass="XmlLexer" 

%{
#define _SKIP_YYFLEXLEXER_
#include "XmlLexer.h"

#define YY_NO_UNISTD_H
#include "XmlParser.hpp"

#define yyterminate() return token::END
#define YY_USER_ACTION  yylloc->columns(yyleng);

#include <cassert>

std::string unescape(const char* str);

%}

string1         \"([^\"\n\r]+|\\\")*\"
string2         \'([^\'\n\r]+|\\\')*\'
number          [-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
identifier      [a-zA-Z_][a-zA-Z0-9_\-\.]*
cdata           <\!\[CDATA\[^(\]\]>)\]\]> 
comment         <\!--^(-->)-->

%%

%{
yylloc->step();
%}



[ \t]+              {                        
                        yylval->string = new std::string(YYText());
                        return token::WS;
                    }

                    
                    
(\n)|(\r\n)|(\r)    {
                        yylloc->lines(1); 
                        yylloc->step();
                        yylval->string = new std::string(YYText());
                        return token::NL;
                    }

{string1}           {
                        yylval->string = new std::string(YYText());
                        return token::STRING;
                    }

{string2}           {
                        yylval->string = new std::string(YYText());
                        return token::STRING;
                    }

{identifier}        {
                        yylval->string = new std::string(YYText());
                        return token::IDENTIFIER;                        
                    }

{cdata}             {
                        // TODO count lines
                        yylval->string = new std::string(YYText());
                        return token::CDATA;                        
                    }

{comment}           {
                        // TODO count lines
                        yylval->string = new std::string(YYText());
                        return token::COMMENT;                        
                    }
                    
"<"                 return token::LT;
"</"                return token::LTS;
">"                 return token::GT;
"/>"                return token::GTS;
"="                 return token::EQUAL;
"<?"                return token::PIO;
"?>"                return token::PIE;
                    
.+                  {
                        yylval->string = new std::string(YYText());
                        return token::CHARS;
                    }


%%

XmlLexer::XmlLexer(std::istream& input, std::ostream& e)
: yylval(NULL), yylloc(NULL), error(e)
{
    switch_streams(&input, NULL);
}
        
int XmlLexer::lex(semantic_type* _yylval, location_type* _yylloc)
{
    this->yylval = _yylval;
    this->yylloc = _yylloc;
    return yylex();
}

int yyFlexLexer::yywrap()
{
    return 1;
}