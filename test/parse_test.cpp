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
        CHECK((bool)root);
        CHECK_EQUAL("document", root->get_name());
    }

    TEST(just_root_node_with_proessing_instruction)
    {
        rxml::Document doc;
        
        std::string xml = 
          "<?xml version=\"1.0\"?>\n"
          "<document />";
        
        std::stringstream buff(xml);
        buff >> doc;
        
        CHECK(doc.has_root_element());
        
        auto root = doc.get_root_element();  
        CHECK((bool)root);               
        CHECK_EQUAL("document", root->get_name());
    } 
    
    TEST(simple_message)   
    {
        rxml::Document doc;
        
        std::string xml = 
          "<?xml version=\"1.0\"?>\n"
          "<message>\n"
          "  <from>rioki</from>\n"
          "  <to>World</to>\n"
          "  <body>Yo I reinvented the wheel.</body>\n"
          "</message>\n";
        
        std::stringstream buff(xml);
        buff >> doc;

        auto xmessage = doc.get_root_element();  
        CHECK((bool)xmessage);               
        CHECK_EQUAL("message", xmessage->get_name());

        auto xfrom = xmessage->find_element("from");
        CHECK((bool)xfrom);
        CHECK_EQUAL("from", xfrom->get_name());
        CHECK_EQUAL("rioki", xfrom->get_text());

        auto xto = xmessage->find_element("to");
        CHECK((bool)xfrom);
        CHECK_EQUAL("to", xto->get_name());
        CHECK_EQUAL("World", xto->get_text());

        auto xbody = xmessage->find_element("body");
        CHECK((bool)xbody);
        CHECK_EQUAL("body", xbody->get_name());
        CHECK_EQUAL("Yo I reinvented the wheel.", xbody->get_text());

        auto children = xmessage->get_children();
        CHECK_EQUAL(7, children.size());
    }

    TEST(parse_attributes)
    {
        rxml::Document doc;
        
        std::string xml = 
          "<?xml version=\"1.0\"?>\n"
          "<screen>"
          "  <button x=\"12\" y='13' text=\"It's Me\"/>\n"
          "</screen>\n";
        
        std::stringstream buff(xml);
        buff >> doc;

        auto xscreen = doc.get_root_element();  

        auto xbutton = xscreen->find_element("button");

        CHECK(xbutton->has_attribute("x"));
        CHECK(xbutton->has_attribute("y"));
        CHECK(xbutton->has_attribute("text"));

        CHECK_EQUAL("12", xbutton->get_attribute("x"));
        CHECK_EQUAL("13", xbutton->get_attribute("y"));
        CHECK_EQUAL("It's Me", xbutton->get_attribute("text"));
        
    }
}
