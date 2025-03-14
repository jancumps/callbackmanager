/*
 * callbackmanager.cpp
 *
 *  Created on: 16 jun. 2024
 *      Author: jancu
 */

module;

#include <concepts>
#include <functional>

export module callbackmanager;

namespace callbackmanager {

// concept guards what types of return values we can handle
template<typename R>
concept Callbackable = 
	std::is_void<R>::value ||
	std::is_arithmetic_v<R> ||
	std::is_class_v<R>;

export template <Callbackable R, typename... Args>
class Callback {
	using callbackfunction_t = std::function<R(Args...)>;	
public:
	Callback() : callback_(nullptr), is_callback_set(false){}
	Callback(callbackfunction_t callback) : 
		callback_(callback), is_callback_set(true){} 

	inline void set(callbackfunction_t callback) {
	    callback_ = callback;
		is_callback_set = true;
	}

	inline void unset() {
		callback_ = nullptr;
		is_callback_set = false;
	}

	[[deprecated("Use operator () instead.")]]
	inline R call(Args... args) {
		return *this(args...);
	}

	inline bool is_set() {
		return is_callback_set;		
	}

	/*
	 * R can be an arithmetic type, an object, or void
	 */
	inline R operator()(Args... args) {
		if constexpr (std::is_void<R>::value) {  // void
			if (!is_callback_set) {
				return;
			} else {
				(callback_)(args...);
			}
		} else if constexpr (std::is_class<R>::value) { // object
			if (!is_callback_set) {
				return R();
			} else {
				return (callback_)(args...);
			}
		} else { // not void nor object
			if (!is_callback_set) {
				return 0; // R can only be a arithmetic type. 0 should work as default.
			} else {
				return (callback_)(args...);
			}
		}
	}

private:
	callbackfunction_t callback_;
	bool is_callback_set;
};

} // namespace callbackmanager