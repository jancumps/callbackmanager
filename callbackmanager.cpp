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
	Callback() : callback_(nullptr), is_callback_set(false){}

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
	 * R can either be an arithmetic type, or void
	 */
	inline R operator()(Args... args) {
		if constexpr (std::is_void<R>::value) {
			if (!is_callback_set) {
				return;
			}
			(callback_)(args...);
		}

		if constexpr (! std::is_void<R>::value) {
			if (!is_callback_set) {
				return 0; // R can only be a arithmetic type. 0 should work as default.
			}
			return (callback_)(args...);
		}
	}

private:
	callbackfunction_t callback_;
	bool is_callback_set;
};

} // namespace callbackmanager