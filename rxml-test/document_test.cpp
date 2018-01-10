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

#include "rtest.h"

#include "rxml/rxml.h"

SUITE(document)
{
    TEST(initial_document_has_no_root_element)
    {
        rxml::Document doc;
        CHECK(! doc.has_root_element());
    }
    
    TEST(create_root_element)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        CHECK((bool)root);
        CHECK_EQUAL("test", root->get_name());     
    }
    
    TEST(get_root_node_throws_on_no_root_element)    
    {
        rxml::Document doc;
        CHECK_THROW(doc.get_root_element(), std::logic_error);
    }
    
    TEST(build_html)
    {
        rxml::Document doc;
        auto html = doc.create_root_element("html");        
        
        auto head = html->add_element("head");        
        auto title = head->add_element("title");
        title->set_text("This is a test HTML.");
        auto style_link = head->add_element("link");
        style_link->set_attribute("rel", "stylesheet");
        style_link->set_attribute("type", "text/css");
        style_link->set_attribute("href", "style.css");
        
        auto body = html->add_element("body");
        auto h1 = body->add_element("h1");
        h1->set_text("This is a test HTML");
        auto p1 = body->add_element("p");
        p1->add_text("This is a test for ");
        auto em1 = p1->add_element("em");
        em1->set_text("rxml");
        p1->add_text(". It aimes to see if a HTML document can be created with the interface.");
        
        std::stringstream buff;
        buff << doc;
        
        std::string ref = 
          "<?xml version=\"1.0\"?>\n"
          "<html><head><title>This is a test HTML.</title>"
          "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\"/></head>"
          "<body><h1>This is a test HTML</h1><p>This is a test for <em>rxml</em>."
          " It aimes to see if a HTML document can be created with the interface.</p></body></html>";
        CHECK_EQUAL(ref, buff.str());
    }
}