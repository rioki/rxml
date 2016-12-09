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

SUITE(element)
{
    TEST(get_name)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        CHECK_EQUAL("test", root->get_name());
    }
    
    TEST(set_name)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_name("root");
        CHECK_EQUAL("root", root->get_name());
    }
    
    TEST(set_text)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_text("This is a test");
        CHECK_EQUAL("This is a test", root->get_text());
    }
    
    TEST(set_cdata)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_cdata("This is a cdata");
        
        CHECK_EQUAL("This is a cdata", root->get_text());
    }
    
    TEST(get_set_attribute)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_attribute("key", "value");
        CHECK(root->has_attribute("key"));
        CHECK_EQUAL("value", root->get_attribute("key"));
    }
    
    TEST(remove_attribute)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_attribute("key", "value");
        root->remove_attribute("key");
        
        CHECK(! root->has_attribute("key"));
    }
    
    TEST(add_element)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        auto element1 = root->add_element("element1");
        CHECK(element1 != NULL);
        CHECK_EQUAL("element1", element1->get_name());
    }
    
    TEST(get_parent)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        auto element1 = root->add_element("element1");
        CHECK_EQUAL(root.get(), element1->get_parent());       
    }
    
    TEST(browse_children)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        auto element1 = root->add_element("element1");    
        auto element2 = root->add_element("element2");
        auto element3 = root->add_element("element3");
        
        auto children = root->get_children();
        CHECK_EQUAL(3, children.size());
        CHECK_EQUAL(element1, children[0]);
        CHECK_EQUAL(element2, children[1]);
        CHECK_EQUAL(element3, children[2]);
    }  

    TEST(get_text_parent)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_text("Hello World!");
        auto children = root->get_children();
        CHECK_EQUAL(1, children.size());
        CHECK_EQUAL(root.get(), children[0]->get_parent());       
    }    
    
    TEST(get_cdata_parent)
    {
        rxml::Document doc;
        auto root = doc.create_root_element("test");
        root->set_cdata("Hello World!");
        auto children = root->get_children();
        CHECK_EQUAL(1, children.size());
        CHECK_EQUAL(root.get(), children[0]->get_parent());       
    } 
}