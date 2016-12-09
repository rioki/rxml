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

#ifndef _RXML_NODE_H_
#define _RXML_NODE_H_

#include <iosfwd>

#include "defines.h"

namespace rxml
{
    /**
     * XML Element
     **/  
    class RXML_EXPORT Node
    {
    public:
        
        Node();
        
        explicit
        Node(Node* parent);
        
        Node(const Node&) = delete;
        
        virtual ~Node();
        
        Node& operator = (const Node&) = delete;
        
        /**
         * Check if the node has a parent.
         **/
        bool has_parent() const;
        
        /**
         * Get the node's parent;
         *
         * @{
         **/
        Node* get_parent();  
        const Node* get_parent() const;        
         /** @} **/
         
        virtual void write(std::ostream& os) const = 0;
        
    private:
        Node* parent;
    };
}

#endif
