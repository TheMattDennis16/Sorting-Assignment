#pragma once
#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

typedef std::string name;
typedef std::unordered_multimap<name, name> umap;

class UnorderedMap 
{
public:
	static void performParsing(std::string file);
};

#endif