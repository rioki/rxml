
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

int count_lines(const std::string& buff);
bool is_ws(const std::string& buff);

%}

%x ELEMENT

nl              "\n"|"\r"|"\r\n"
ws              [ \t\v]+
string1         \"([^\"\n\r]+|\\\")*\"
string2         \'([^\'\n\r]+|\\\')*\'
number          [-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
name            [a-zA-Z_][a-zA-Z0-9_\-\.]*
cdata           <\!\[CDATA\[^(\]\]>)\]\]> 
comment         <\!--^(-->)-->
text            [^<]+

%%

%{
yylloc->step();
%}

{comment}               {
                            yylval->string = new std::string(YYText());
                            int ln = count_lines(*yylval->string);
                            yylloc->lines(ln); 
                            yylloc->step();
                            return token::COMMENT;                        
                        }

{cdata}                 {
                            yylval->string = new std::string(YYText());
                            int ln = count_lines(*yylval->string);
                            yylloc->lines(ln); 
                            yylloc->step();
                            return token::CDATA;                        
                        }

{text}                  {
                            yylval->string = new std::string(YYText());
                            int ln = count_lines(*yylval->string);
                            yylloc->lines(ln); 
                            yylloc->step();
                            if (is_ws(*yylval->string))
                            {
                                return token::WS;
                            }
                            else
                            {
                                return token::TEXT;  
                            }                            
                        }
                    
"<"                     {
                            BEGIN(ELEMENT);
                            return token::LT;
                        }
"</"                    {
                            BEGIN(ELEMENT);
                            return token::LTS;
                        }

"<?"                    { 
                            BEGIN(ELEMENT);
                            return token::PIO;
                        }

<ELEMENT>{name}         {
                            yylval->string = new std::string(YYText());
                            return token::NAME;  
                        } 

<ELEMENT>{string1}      {
                            size_t l = strlen(YYText());
                            yylval->string = new std::string(YYText()+1, l - 2);
                            return token::STRING;
                        }

<ELEMENT>{string2}      {
                            size_t l = strlen(YYText());
                            yylval->string = new std::string(YYText()+1, l - 2);
                            return token::STRING;
                        }

<ELEMENT>"="            return token::EQUAL;

<ELEMENT>{ws}           return token::WS;

<ELEMENT>{nl}           {
                            yylloc->lines(1); 
                            yylloc->step();
                            return token::NL;
                        }

<ELEMENT>">"            {
                            BEGIN(INITIAL);
                            return token::GT;
                        }

<ELEMENT>"/>"           {
                            BEGIN(INITIAL);
                            return token::GTS;
                        }

<ELEMENT>"?>"           {
                            BEGIN(INITIAL);
                            return token::PIE;
                        }
                    
.                       return token::ERROR;

%%

int count_lines(const std::string& buff)
{
    int ln = 0;
    bool r_seen = false;
    for (char c : buff)
    {
        if (c == '\n' && !r_seen)
        {
            ln++;             
        }
        else if (c == '\r')
        {
            ln++;
            r_seen = true;
        }
        else
        {
            r_seen = false;
        }
    }
    return ln;
}

bool is_ws(const std::string& buff)
{
    return buff.find_first_not_of(" \t\v\n\r") == std::string::npos;
}

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