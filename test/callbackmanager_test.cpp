#include <gtest/gtest.h>

import callbackmanager;

// scenario: call object method
TEST(callback, objectMethod) {
    class MyClass {
    public:
        inline int handler(const int& num1, const int& num2) const {
            return num1 + num2;
        }
    };

    MyClass myClass;

    callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to capture myClass and call the object method
    cb.set([&myClass](const int& num1, const int& num2) -> int {
        return myClass.handler(num1, num2);
    });    
    ASSERT_EQ(cb.call(4, 5), 9);
    ASSERT_NE(cb.call(4, 5), 8);
}

// scenario: call static method
TEST(callback, classStaticMethod) {
    class MyClass {
    public:
        static inline int staticHandler(const int& num1, const int& num2) {
            return num1 + num2;
        }
    };

	callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to call the static method
    cb.set([](const int& num1, const int& num2) -> int {
        return MyClass::staticHandler(num1, num2);
    });
    ASSERT_EQ(cb.call(4, 5), 9);
    ASSERT_NE(cb.call(4, 5), 8);
}

// scenario: call C function
int functionHandler(const int& num1, const int& num2) {
    return num1 + num2;
}

TEST(callback, cFunction) {
    callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to call the classic C function
    cb.set([](const int& num1, const int& num2) -> int {
        return functionHandler(num1, num2);
    });
    ASSERT_EQ(cb.call(4, 5), 9);
    ASSERT_NE(cb.call(4, 5), 8);
}

// scenario: call pure lambda
TEST(callback, lambda) {
	callbackmanager::Callback<int, const int&, const int&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const int& num1, const int& num2) -> int {
        return num1 + num2;
    });
    ASSERT_EQ(cb.call(4, 5), 9);
    ASSERT_NE(cb.call(4, 5), 8);
}

// scenario: return a bool
TEST(callback, bool) {
	callbackmanager::Callback<bool, const int&, const int&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const int& num1, const int& num2) -> bool {
        return num1 == num2;
    });
	ASSERT_TRUE(cb.call(1, 1));
	ASSERT_FALSE(cb.call(1, 2));
}

// scenario: use void, and no attributes
TEST(callback, voidWithoutParameters) {
	callbackmanager::Callback<void> cb;
    // Use a lambda to execute anonymous C code
    bool called = false;
    cb.set([&called]() {
        called = true;
        return;
    });
    cb.call();
    ASSERT_TRUE(called);
}

// scenario: use void, and a const std::string reference
TEST(callback, voidWithConstParameter) {
    callbackmanager::Callback<void, const std::string&> cb;
    // Use a lambda to execute anonymous C code
    cb.set([](const std::string& s) {
        ASSERT_STREQ(s.c_str(), "test");
        return;
    });
    cb.call("test");
}    

// scenario: no handler
TEST(callback, noHandler) {
	callbackmanager::Callback<void> cb;
    ASSERT_FALSE(cb.is_set());
    cb.call();
    ASSERT_TRUE(true); // call without callback should succeed
}    

// scenario: set and unset
TEST(callback, setUnset) {
	callbackmanager::Callback<void> cb;
    ASSERT_FALSE(cb.is_set());
    // Use a lambda to execute anonymous C code
    cb.set([]() {
        return;
    });
    ASSERT_TRUE(cb.is_set());
    cb.unset();
    ASSERT_FALSE(cb.is_set());
}    