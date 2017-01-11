// 
// rxml - rioki's xml lbrary
// Copyright 2016-2017 Sean "rioki" Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 

#include "SaxParser.h"

#include <sstream>

#include "XmlLexer.h"
#include "XmLParser.hpp"

namespace rxml
{
    SaxParser::SaxParser(std::istream& i, const std::string& f)
    : input(i), file(f) {}

    SaxParser::~SaxParser() {}

    void SaxParser::on_start_element(std::function<void (const std::string&, const std::map<std::string, std::string>&)> cb)
    {
        start_element_cb = cb;
    }

    void SaxParser::on_end_element(std::function<void (const std::string&)> cb)
    {
        end_element_cb = cb;
    }

    void SaxParser::on_text(std::function<void (const std::string&)> cb)
    {
        text_cb = cb;
    }

    void SaxParser::on_cdata(std::function<void (const std::string&)> cb)
    {
        cdata_cb = cb;
    }

    void SaxParser::parse()
    {
        std::stringstream error;
        
        XmlLexer lexer(input, error);
        parser prs(lexer, *this, error, file);
        int r = prs.parse();
        
        if (r != 0)
        {
            throw std::runtime_error(error.str());
        }
    }
}
