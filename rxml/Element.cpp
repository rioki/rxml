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

#include "Element.h"

#include <iostream>

#include "Text.h"
#include "CData.h"

namespace rxml
{
    Element::Element(const std::string& n)
    : name(n) {}
    
    Element::Element(Element* parent, const std::string& n)
    : Node(parent), name(n) {}
    
    const std::string& Element::get_name() const
    {
        return name;
    }
        
    void Element::set_name(const std::string& value)
    {
        name = value;
    }
    
    bool Element::has_attribute(const std::string& name) const
    {
        return attributes.find(name) != attributes.end();
    }

    const std::string& Element::get_attribute(const std::string& name) const
    {
        auto i = attributes.find(name);
        if (i != attributes.end())
        {
            return i->second;
        }
        else
        {
            throw std::logic_error(__FUNCTION__);
        }
    }

    void Element::set_attribute(const std::string& name, const std::string& value)
    {
        attributes[name] = value;
    }

    void Element::remove_attribute(const std::string& name)
    {
        auto i = attributes.find(name);
        if (i != attributes.end())
        {
            attributes.erase(i);
        }
        else
        {
            throw std::logic_error(__FUNCTION__);
        }
    }

    void Element::set_attributes(const std::map<std::string, std::string>& value)
    {
        attributes = value;
    }

    const std::map<std::string, std::string>& Element::get_attributes() const
    {
        return attributes;
    }
    
    std::string Element::get_text() const
    {
        if (children.size() == 0)
        {
            return "";
        }
        if (children.size() == 1)
        {
            auto text_node = std::dynamic_pointer_cast<Text>(children[0]);
            if (text_node)
            {
                return text_node->get_value();
            }
            else
            {
                auto cdata_node = std::dynamic_pointer_cast<CData>(children[0]);
                if (cdata_node)
                {
                    return cdata_node->get_value();
                }
                else
                {
                    throw std::runtime_error(__FUNCTION__);
                }
            }
            
        }
        throw std::runtime_error(__FUNCTION__);                
    }
        
    void Element::set_text(const std::string& text)
    {
        children.clear();
        add_text(text);
    }
    
    void Element::add_text(const std::string& text)
    {
        children.push_back(std::make_shared<Text>(this, text));
    }
    
    void Element::set_cdata(const std::string& text)
    {
        children.clear();
        children.push_back(std::make_shared<CData>(this, text));
    }
    
    void Element::add_cdata(const std::string& text)
    {
        children.push_back(std::make_shared<CData>(this, text));
    }
    
    
    std::shared_ptr<Element> Element::add_element(const std::string& name)
    {
        auto element = std::make_shared<Element>(this, name);
        children.push_back(element);
        return element;
    }

    std::vector<std::shared_ptr<Node>> Element::get_children() const
    {
        return children;
    }

    std::shared_ptr<Element> Element::find_element(const std::string& name)
    {
        for (auto child : children)
        {
            auto element = std::dynamic_pointer_cast<Element>(child);
            if (element && element->get_name() == name)
            {
                return element;
            }
        }
        return nullptr;
    }
    
    void Element::write(std::ostream& os) const
    {
        os << "<" << name;
        
        for (auto i = attributes.begin(); i != attributes.end(); ++i)
        {
            // TODO escape special chars
            os << " " << i->first << "=\"" << i->second << "\"";
        }
        
        if (children.empty())
        {
            os << "/>";
        }
        else
        {
            os << ">";
            
            for (auto j = children.begin(); j != children.end(); ++j)
            {
                (*j)->write(os);
            }
            os << "</" << name << ">";
        }        
    }
}
