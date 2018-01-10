// 
// rxml - rioki's xml lbrary
// Copyright 2016-2018 Sean "rioki" Farrell <sean.farrell@rioki.org>
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
#include <fstream>
#include <sstream>
#include <stack>

#include "Element.h"
#include "SaxParser.h"

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

    void Document::read(const std::string& file)
    {
        std::ifstream in(file);
        if (in.is_open())
        {
            in >> *this;
        }
        else
        {
            std::stringstream buff;
            buff << "Failed to open " << file << " for reading.";
            throw std::runtime_error(buff.str());
        }
    }

    void Document::write(const std::string& file)
    {
        std::ofstream out(file);
        if (out.is_open())
        {
            out << *this;
        }
        else
        {
            std::stringstream buff;
            buff << "Failed to open " << file << " for writing.";
            throw std::runtime_error(buff.str());
        }
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
        std::stack<std::shared_ptr<Element>> elements;

        SaxParser parser(is);
        
        parser.on_start_element([&] (const std::string& name, const std::map<std::string, std::string>& attributes) {
            std::shared_ptr<Element> element;
            if (elements.empty())
            {
                element = doc.create_root_element(name);
            }
            else
            {
                element = elements.top()->add_element(name);
            }
            element->set_attributes(attributes);
            elements.push(element);
        });

        parser.on_end_element([&] (const std::string& name) {
            if (elements.top()->get_name() != name)
            {
                // TODO location
                throw std::runtime_error("Mismatched elements.");
            }
            elements.pop();
        });

        parser.on_text([&] (const std::string& text) {
            if (elements.empty())
            {
                throw std::runtime_error("strey text");
            }
            elements.top()->add_text(text);
        });
        
        parser.on_cdata([&] (const std::string& text) {
            if (elements.empty())
            {
                throw std::runtime_error("strey cdata");
            }
            elements.top()->add_cdata(text);
        });

        parser.on_comment([&] (const std::string& text) {
            if (elements.empty())
            {
                // This is allowed, but there is no nice place to put it...
            }
            else
            {
                elements.top()->add_comment(text);
            }            
        });
        
        parser.parse();
        
        return is;
    }
}
