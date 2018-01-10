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

#ifndef _RXML_CONTENT_H_
#define _RXML_CONTENT_H_

#include <string>

#include "Node.h"

namespace rxml
{
    /**
     * XML Text, CData base class.
     **/  
    class RXML_EXPORT Content : public Node
    {
    public:
        /**
         * Construct a content node.
         **/
        Content();
        
        /**
         * Initialize a content node.
         **/
        explicit
        Content(const std::string& value);
        
        Content(Node* parent, const std::string& value);        
        
        /**
         * Get the value of this node. 
         *
         * @return Returns the value of this node or empty if not found.
         **/
        const std::string& get_value() const;
        
        /**
         * Set the value of this node.
         *
         * @param value the value to set.
         **/
        void set_value(const std::string& value);        
        
        /**
         * Check if a given note is a blank node.
         **/
        bool is_blank() const;  
        
    protected:
        std::string value;
    };
}

#endif
