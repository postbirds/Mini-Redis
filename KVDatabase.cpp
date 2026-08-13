#include "KVDatabase.h"
#include <iostream>

void KVDatabase::set(const std::string& key, const std::string& value) {
	store[key] = value;
	std::cout << "[SET] " << key << " = " << value << "\n";
}

std::string KVDatabase::get(const std::string& key) {
	if(store.find(key) != store.end()){
		return store[key];
	}
	return "(nil)";
}