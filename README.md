# callbackmanager
C++ callback manager supports classic C function, a lambda, a static class method or an object method as handler

[![Open Source](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://opensource.org/)
![GitHub License](https://img.shields.io/github/license/jancumps/callbackmanager?label=licence)
[![run unit tests](https://github.com/jancumps/callbackmanager/actions/workflows/test.yml/badge.svg)](https://github.com/jancumps/callbackmanager/actions/workflows/test.yml)

This callback manager can execute a method of a particular object as a callback. 
It can be used in typical callback situations, e.g.: in a UART driver or a GUI framework. But also in interrupt handlers.

- lightweight: small runtime cost, low firmware hit. Can be used for tiny embedded systems.
- reusable: the library doesn't assume parameters and types for the handler.
- object oriented, modern C++ constructs -> std::function, lambda, C++ templates, type traits.
- type-safe
- allow a classic C function, a lambda, a static class method or an object method as handler. 
- pass handler arguments by value, by reference, as const
- allow handlers that return void, bool, arithmetic, or an object.

### Blog:

[see article on element14](https://community.element14.com/products/devtools/software/f/forum/54719/c-callbacks-and-templates)  

[and a follow-up that shows different callback options (object method, static class method, C function, lambda)](https://community.element14.com/products/devtools/software/f/forum/54721/c-callbacks-and-templates-make-the-callback-class-call-an-object-member-a-static-member-a-c-function-and-a-pure-lambda-function)  
