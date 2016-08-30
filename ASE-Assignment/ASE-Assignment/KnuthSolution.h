#ifndef KNUTH_HH
#define KNUTH_HH

/*
	Based on a proposed solution in the third volume of The Art of Computer Programming.
	Not fully functional. Removed from compilation process.
*/

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <list>
#include <vector>

typedef std::string name;
typedef std::list<std::pair<name, name>> fileCopy;

class KnuthSolution
{
private:
	std::string filename;

	fileCopy readFile(std::string fileIn);
	fileCopy swapKeyValue(fileCopy& original);
	std::pair<name, name> atIndex(fileCopy& container, int index);
	template<typename T> void advanceIterator(T& it, fileCopy file);

public:
	KnuthSolution(std::string file);
	void solve();
	void writeToFile(fileCopy& file, std::string fileNameToWrite);
};

#endif

template<typename T>
inline void KnuthSolution::advanceIterator(T & it, fileCopy file)
{
	auto copyIt = it;
	if (copyIt++ == file.end())
	{
		std::cout << "Resetting size: " << file.size() << " it" << std::endl;
		it = file.begin();
	}
	else
	{
		it++;
		std::cout << "Advancing size: " << file.size() << " it" << std::endl;
	}
}
