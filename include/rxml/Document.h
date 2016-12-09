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

#ifndef _RXML_DOCUMENT_H_
#define _RXML_DOCUMENT_H_

#include <memory>
#include <string>
#include <iosfwd>

#include "defines.h"

namespace rxml
{
    class Element;
    
    /**
     * XML DOM Document
     *
     * This class is the root class for the XML DOM.
     **/  
    class RXML_EXPORT Document
    {
    public:
        /** 
         * Default Constructor
         **/
        Document();
        
        Document(const Document&) = delete;
        
        Document& operator = (const Document&) = delete;
        
        /**
         * Check if the document has a root element.
         *
         * @return true if the document has a root element.
         **/
        bool has_root_element() const;
        
        /**
         * Get the root element.
         *
         * @return The root element.
         *
         * @exception NoRootElement Throws NoRootElement if the document has
         * no root element.
         *
         * @{
         **/
        std::shared_ptr<Element> get_root_element();
        const std::shared_ptr<Element> get_root_element() const;
        /** @} **/   
        
        void set_root_element(std::shared_ptr<Element> value);
                
        /**
         * Create the root element of a document.
         *
         * @param name The name of the root node.
         *
         * @return The root element.
         *
         * @exception std::logic_error Throws logic_error if the document already
         * has a root element.
         **/
        std::shared_ptr<Element> create_root_element(const std::string& name);
        
        void write(std::ostream& os) const;
        
    private:
        std::shared_ptr<Element> root_element;
    };
    
    RXML_EXPORT
    std::ostream& operator << (std::ostream& os, const Document& doc);
    
    RXML_EXPORT
    std::istream& operator >> (std::istream& is, Document& doc);
}

#endif
