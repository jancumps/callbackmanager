// https://blog.mbedded.ninja/programming/languages/c-plus-plus/callbacks/

#include <cstdio>
#include <functional>

class LibraryClass {
public:
	LibraryClass() : _callback(nullptr){}
	void passACallbackToMe(std::function<int(int, int)> callback) {
	    _callback = & callback;
	}
	void callCallback() {
		if (_callback == nullptr) {
			return;
		}
		// Now invoke (call) the callback
		int o = (*_callback)(1, 2);
        printf("Value: %i\n", o); // We might be on an embedded system, use printf() and not std::cout

	}
private:
	std::function<int(int, int)> *_callback;
};

class MyClass {
public:
      int methodToCallback(int num1, int num2) {
          return num1 + num2;
      }
};

int main()
{
    MyClass myClass;

    LibraryClass libraryClass;
    // Use a lambda to capture myClass and call the member method
    libraryClass.passACallbackToMe([&myClass](int num1, int num2) -> int {
        return myClass.methodToCallback(num1, num2);
    });

    libraryClass.callCallback();
}
