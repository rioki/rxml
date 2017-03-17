
# rxml

## Is rxml standard compliment? 

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

License
-------

Copyright 2016-2017 Sean "rioki" Farrell <sean.farrell@rioki.org>

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
  