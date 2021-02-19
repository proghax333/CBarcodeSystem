
#pragma once

#include <string>
#include "pair.h"

using namespace std;

class UPC : public Pair<long long, string> {
	public:
		UPC() = default;
		
		UPC(key_type key) :
			Pair(key)
		{ }
		UPC(key_type key, const value_type& value) :
			Pair(key, value)
		{ }
		
		UPC(const UPC& other) {
			key = other.key;
			value = other.value;
		}
		
		virtual ~UPC() { }
};
