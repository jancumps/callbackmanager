/*
 * callbackmanager.cpp
 *
 *  Created on: 16 jun. 2024
 *      Author: jancu
 */

 module;

 #include <functional>
 
 export module callbackmanager;
 
 namespace callbackmanager {
 
 export template <typename R, typename... Args>
  requires std::is_void<R>::value || std::is_arithmetic_v<R>
class Callback {
	using callbackfunction_t = std::function<R(Args...)>;	
public:
	Callback() : callback_(nullptr), isSet(false){}

	inline void set(callbackfunction_t callback) {
	    callback_ = callback;
		isSet = true;
	}

	inline void unset() {
		callback_ = nullptr;
		isSet = false;
	}

	/*
	 * R can either be an arithmetic type, or void
	 */
	inline R call(Args... args) {
		if constexpr (std::is_void<R>::value) {
			if (!isSet) {
				return;
			}
			(callback_)(args...);
		}

		if constexpr (! std::is_void<R>::value) {
			if (!isSet) {
				return 0; // R can only be a arithmetic type. 0 should work as default.
			}
			return (callback_)(args...);
		}
	}

	inline bool is_set() {
		return isSet;		
	}

private:
	callbackfunction_t callback_;
	bool isSet;
};

} // namespace callbackmanager