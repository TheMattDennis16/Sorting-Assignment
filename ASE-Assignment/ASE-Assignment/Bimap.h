#pragma once
#ifndef BIMAP_H
#define BIMAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <boost/bimap.hpp>

typedef std::string name;
typedef boost::bimap<name, name> map;
typedef map::value_type values;

class Bimap
{
public:
	static void performParsing(std::string file);
};

#endif