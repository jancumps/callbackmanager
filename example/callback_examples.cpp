// https://community.element14.com/products/devtools/software/f/forum/54719/c-callbacks-and-templates


#include <cstdio>
#include <string>
#include <typeinfo>

import callbackmanager;

class MyClass {
public:
	inline int handler(const int& num1, const int& num2) const {
          return num1 + num2;
      }
      static inline int staticHandler(const int& num1, const int& num2) {
          return num1 + num2;
      }
};

int functionHandler(const int& num1, const int& num2) {
    return num1 + num2;
}
 
int main() {

    int a = 4;
    int b = 5;

	{ // scenario: call object method
    MyClass myClass;

    callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to capture myClass and call the object method
    cb.set([&myClass](const int& num1, const int& num2) -> int const {
        return myClass.handler(num1, num2);
    });

    int o = cb(a, b);
    printf("Value: %i\n", o);
	fflush(stdout);
	}

	{ // scenario: call static method
	callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to call the static method
    cb.set([](const int& num1, const int& num2) -> int {
        return MyClass::staticHandler(num1, num2);
    });

    int o = cb(a, b);
    printf("Value: %i\n", o);
	fflush(stdout);
	}

	{ // scenario: call C function
	callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to call the classic C function
    cb.set([](const int& num1, const int& num2) -> int {
        return functionHandler(num1, num2);
    });

    int o = cb(a, b);
    printf("Value: %i\n", o);
	fflush(stdout);
	}

	{ // scenario: call pure lambda
	callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const int& num1, const int& num2) -> int {
        return num1 + num2;
    });

    int o  = cb(a, b);
    printf("Value: %i\n", o);
	fflush(stdout);
	}

	{ // scenario: return a bool
	callbackmanager::Callback<bool, const int&, const int&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const int& num1, const int& num2) -> bool {
        return num1 == num2;
    });

    printf("Value: %s\n", cb(a, b) ? "true" : "false");
	fflush(stdout);
	}

	{ // scenario: use void
	callbackmanager::Callback<void, const int&, const int&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const int& num1, const int& num2) {
        printf("void gets num1: %i, num2: %i\n", num1, num2);
    	fflush(stdout);
        return;
    });
    cb(a, b);
	}

	{ // scenario: use void, and no attributes
	callbackmanager::Callback<void> cb;
    // Use a lambda to execute anonymous C code
    cb.set([]() {
        printf("void with no parameters\n");
    	fflush(stdout);
        return;
    });
    cb();
	}

	{ // scenario: use void, and a const std::string reference
	callbackmanager::Callback<void, const std::string&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const std::string& s) {
        printf("%s", s.c_str());
    	fflush(stdout);
        return;
    });
    cb("hello, world!\r\n");
	}

	{ // scenario: use void, and a const std::string reference
	std::string updateme;
	callbackmanager::Callback<void, std::string&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](std::string& s) {
    	s.assign("hello, world!\r\n");
        return;
    });
    cb(updateme);
    printf("%s", updateme.c_str());
	fflush(stdout);
	}

    { // scenario: return an object
    class return_class {
    public:
        return_class() : value_(0) {};
        int value_;
    };

	callbackmanager::Callback<return_class> cb;
    // Use a lambda to execute anonymous C code
    cb.set([]() -> return_class {
        return_class rc;
        rc.value_ = 1;
        return rc;
    });
    return_class ret = cb();
    printf("Value: %d\n", ret.value_ );
	fflush(stdout);
	}

	{ // scenario: constructor with lambda
    callbackmanager::Callback<bool, const int&, const int&> cb(
        [](const int& num1, const int& num2) -> bool {
            return num1 == num2;
    });
    
    printf("Value: %s\n", cb(a, b) ? "true" : "false");
    fflush(stdout);
    }    
	
	// { // scenario: use an unsupported (non-fundamental) type for return value R
	//   // this will generate a compile error
    // callbackmanager::Callback<char[], const int&, const int&> cb;
	// }

}

