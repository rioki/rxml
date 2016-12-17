// 
// rxml - rioki's xml lbrary
// Copyright 2016 Sean "rioki" Farrell <sean.farrell@rioki.org>
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

#ifndef _RXML_SAXPARSER_H_
#define _RXML_SAXPARSER_H_

#include <iosfwd>
#include <string>
#include <map>
#include <functional>

#include "defines.h"

namespace rxml
{
    /**
     * Serial Access to XML Parser API
     **/  
    class RXML_EXPORT SaxParser
    {
    public:
        
        SaxParser(std::istream& input, const std::string& file = "stream");

        SaxParser(const SaxParser&) = delete;

        ~SaxParser();

        SaxParser& operator = (const SaxParser&) const = delete;        

        void on_start_element(std::function<void (const std::string&, const std::map<std::string, std::string>&)> cb);

        void on_end_element(std::function<void (const std::string&)> cb);

        void on_text(std::function<void (const std::string&)> cb);

        void on_cdata(std::function<void (const std::string&)> cb);

        void parse();

    private:
        std::istream& input;
        std::string   file;
    
        std::function<void (const std::string&, const std::map<std::string, std::string>&)> start_element_cb;
        std::function<void (const std::string&)>                                            end_element_cb;
        std::function<void (const std::string&)>                                            text_cb;
        std::function<void (const std::string&)>                                            cdata_cb;

    friend class parser;
    };
}

#endif
