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

#ifndef _RXML_ELEMENT_H_
#define _RXML_ELEMENT_H_

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Node.h"

namespace rxml
{
    /**
     * XML Element
     **/  
    class RXML_EXPORT Element : public Node
    {
    public:
        
        explicit
        Element(const std::string& name);
        
        Element(Element* parent, const std::string& name);
        
        /**
         * Get the node's name.
         **/
        const std::string& get_name() const;
        
        /**
         * Set a node's name.
         **/
        void set_name(const std::string& value);
        
        /**
         * Check if a given attribute exists.
         **/
        bool has_attribute(const std::string& name) const;
        
        /** 
         * Get a given attribute. 
         *         
         * This method will retrive an attribute.
         *
         * @param name the attribtue name
         * @return the attribute value
         *
         * @throws no_such_attribute if the attibute does not exist on
         * this element.
         **/
        const std::string& get_attribute(const std::string& name) const;
        
        /**
         * Set an attribute.
         **/
        void set_attribute(const std::string& name, const std::string& value);
        
        /**
         * Remove a given attribute.
         **/
        void remove_attribute(const std::string& name);
        
        /**
         * Get the element's text or cdata. Empty if not found.
         * 
         * @tood Merge multiple text bits?          
         **/
        std::string get_text() const;
        
        /**
         * Set the element's text.
         **/
        void set_text(const std::string& text);
        
        /**
         * Append text to the element.
         **/
        void add_text(const std::string& text);
        
        /**
         * Set the element's CData
         **/
        void set_cdata(const std::string& text);
       
        /**       
         * Add a element.
         **/
        std::shared_ptr<Element> add_element(const std::string& name);
        
        /**
         * Get all children of this element.
         *
         * @return All children of this element. 
         **/
        std::vector<std::shared_ptr<Node>> get_children() const;

        std::shared_ptr<Element> find_element(const std::string& name);
        
        virtual void write(std::ostream& os) const override;
        
    private:
        Element* parrent;
        std::string name;
        std::map<std::string, std::string> attributes;
        std::vector<std::shared_ptr<Node>> children;
    };
}

#endif
