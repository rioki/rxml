
# rxml

rxml is an XML parser that implements the sensible XML subset.

## Example

Assume you have the following piece of XML:

    <?xml version=\"1.0\" ?>
    <message from="rioki" to="World">      
      <body>Yo! I reinvented the wheel.</body>
    </message>

To parse the XML you would to the following:

    std::string from, to, body;
    
    rxml::Document xdoc;
    xdoc.read("message.xml");

    auto xmessge = xdoc.get_root_element();
    if (xmessage || xmessage->get_name() == "message")
    {
        throw std::runtime_error("Message has not root element message.");
    }

    if (xmessage->has_attribute("from"))
    {
        from = xmessage->get_attribute("from")
    }

    if (xmessage->has_attribute("to"))
    {
        to = xmessage->get_attribute("to")
    }

    auto xbody = xmessage->find_element("from");
    if (xbody)
    {
        body = xbody->get_text();
    }

To write a XML document, you would do the following:

    rxml::Document xdoc;
    
    auto xmessage = xdoc.create_root_element("message");

    xmessage->set_attribute("from", "mom");
    xmessage->set_attribute("to", "rioki");

    auto xbody = xmessage->add_element("body");
    xbody->set_text("That is nice, hun.");

    xdoc.write("reply.xml");

## Building (POSIX)

To build rxml you need a C++ compiler (e.g. gcc), make, bison and flex. These 
are things you should have lying around anyway.

The build the library simply run make in the root directory of rxml:

    make

If you want to check the consistency library on your machine you may also want to run the check target.

    make check

To install the library into your system you simply call the install target:

    make install

If you want to control where the library is installed you can specify this with the prefix variables, like so:

    prefix=$HOME/libs make install

If you want to remove the library from your system, use the uninstall target:

    make uninstall

As with the install target you can specify the prefix variable.

## Building (Visual Studio)

The project contains VS2017 build configuration for 32 and 64 Bit builds.

## Is rxml standard compliant?

Short answer:

**NO**

Long answer:

XML is a useful technology, but somewhere in the late 90s the W3C standard 
comity went overboard. As a result this library only supports the sensible 
subset of XML.

To be specific the following things are not sported:

* namespaces
* parsing DTDs 
* validation (neither DTD nor schema)
* entity replacement (except the built in entities)
* the order of attributes is not preserved


## License

Copyright 2016-2018 Sean "rioki" Farrell <sean.farrell@rioki.org>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
