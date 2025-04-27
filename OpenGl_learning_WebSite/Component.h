#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

template<typename ownertype>
class Component {

public:

	 virtual ~Component() = default;

	 virtual void Init() {};

	 virtual void Loop() {};
			 
	 virtual void Shutdown() {};

	//std::unordered_map <std::string, Component<ownertype>*> Brothers;

};
