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

#include "rtest.h"

#include "rxml/rxml.h"

SUITE(document)
{
    TEST(just_root_node)
    {
        rxml::Document doc;
        
        std::string xml = 
          "<document />";
        
        std::stringstream buff(xml);
        buff >> doc;
        
        CHECK(doc.has_root_element());
        
        auto root = doc.get_root_element();                 
        CHECK_EQUAL("document", root->get_name());
    }

    TEST(just_root_node_with_proessing_instruction)
    {
        rxml::Document doc;
        
        std::string xml = 
          "<?xml version=\"1.0\"?>"
          "<document />";
        
        std::stringstream buff(xml);
        buff >> doc;
        
        CHECK(doc.has_root_element());
        
        auto root = doc.get_root_element();                 
        CHECK_EQUAL("document", root->get_name());
    } 
    
    TEST(simple_message)   
    {
        rxml::Document doc;
        
        std::string xml = 
          "<?xml version=\"1.0\"?>"
          "<message>\n"
          "  <from>rioki</from>\n"
          "  <to>World</to>\n"
          "  <body>Yo I reinvented the wheel.</body>\n"
          "</message>\n";
        
        std::stringstream buff(xml);
        buff >> doc;
        
        auto xmessage = doc.get_root_element();                 
        CHECK_EQUAL("message", xmessage->get_name());
        
        auto xfrom = xmessage->find_element("from");
        CHECK((bool)xfrom);
        
    }
}
