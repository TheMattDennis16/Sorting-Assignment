#include <chrono>
#include "Bimap.h"
#include "UnorderedMap.h"
#define DURATION microseconds
//#include "KnuthSolution.h"

int main()
{
	std::string file = "10.txt";

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Bimap::performParsing(file);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::DURATION>(t2 - t1).count();

	std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
	UnorderedMap::performParsing(file);
	std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::DURATION>(t4 - t3).count();

	std::cout << "Bimap: " << duration1 << " nanoseconds.        Unordered_Map: " << duration2 << " nanoseconds" << std::endl;
}