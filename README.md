
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
