
#pragma once

template<class T, class U>
class Pair {
	public:
		T key;
		U value;
		
		using key_type = T;
		using value_type = U;
		
		Pair() = default;
		
		Pair(const T& key) :
			key(key)
		{ }
		
		Pair(const T& key, const U& value) :
			key(key),
			value(value)
		{ }
		
		virtual ~Pair() { }
};
