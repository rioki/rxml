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

#include "Document.h"

#include <iostream>
#include <sstream>

#include "Element.h"
#include "XmlLexer.h"
#include "XmLParser.hpp"

namespace rxml
{
    Document::Document() {}
    
    bool Document::has_root_element() const
    {
        return (bool)root_element;
    }
    
    std::shared_ptr<Element> Document::get_root_element()
    {
        if (!root_element)
        {
            throw std::logic_error(__FUNCTION__);
        }
        return root_element;
    }
    
    const std::shared_ptr<Element> Document::get_root_element() const
    {
        if (!root_element)
        {
            throw std::logic_error(__FUNCTION__);
        }
        return root_element;
    }
    
    void Document::set_root_element(std::shared_ptr<Element> value)
    {
        root_element = value;
    }
    
    std::shared_ptr<Element> Document::create_root_element(const std::string& name)
    {
        if (root_element)
        {
            throw std::logic_error(__FUNCTION__);
        }
        
        root_element = std::make_shared<Element>(name);
        return root_element;
    }
    
    void Document::write(std::ostream& os) const
    {
        if (root_element)
        {
            os << "<?xml version=\"1.0\"?>\n";
            root_element->write(os);
        }        
    }
    
    std::ostream& operator << (std::ostream& os, const Document& doc)
    {
        doc.write(os);
        return os;
    }
    
    std::istream& operator >> (std::istream& is, Document& doc)
    {
        std::stringstream error;
        std::string filename;
        
        XmlLexer lexer(is, error);
        parser prs(lexer, doc, error, filename);
        int r = prs.parse();
        
        if (r != 0)
        {
            throw std::runtime_error(error.str());
        }
        
        return is;
    }
}
