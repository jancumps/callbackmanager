# callbackmanager
C++ callback manager supports classic C function, a lambda, a static class method or an object method as handler

This callback manager can execute a method of a particular object as a callback. 
It can be used in typical callback situations, e.g.: in a UART driver. But also in interrupt handlers.

- lightweight: small runtime cost, low firmware hit. Can be used for tiny embedded systems.
- reusable: don't assume parameters and types for the handler, in this little framework -> C++ templates
- object oriented, modern C++ constructs -> std::function, lambda, again C++ templates
- type-safe -> again C++ templates
- allow a classic C function, a lambda, a static class method or an object method as handler. 
- pass handler arguments by value, by reference, as const

### Blog:

[see article on element14](https://community.element14.com/products/devtools/software/f/forum/54719/c-callbacks-and-templates)  

[and a follow-up that shows different callback options (object method, static class method, C function, lambda)](https://community.element14.com/products/devtools/software/f/forum/54721/c-callbacks-and-templates-make-the-callback-class-call-an-object-member-a-static-member-a-c-function-and-a-pure-lambda-function)  