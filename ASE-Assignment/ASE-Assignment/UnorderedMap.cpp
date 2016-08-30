#include "UnorderedMap.h"



void UnorderedMap::performParsing(std::string filein)
{
	umap nameMap;
	umap backMap;

	const std::string filepath = filein;
	const char parsingChar = ',';
	std::ifstream file;
	int maxSize = 0;

	file.open(filepath, std::ifstream::in);
	if (file.is_open())
	{
		std::string line = "";
		name currName;
		std::vector<std::string> names;
		while (std::getline(file, line))
		{
			std::istringstream strStream(line);
			while (std::getline(strStream, currName, parsingChar))
			{
				//Trim all names to the 8 length limit.
				names.push_back(currName);
			}
			if (names.size() > 0)
			{
				nameMap.insert(std::make_pair(names[0], names[1]));
				backMap.insert(std::make_pair(names[1], names[0]));
				maxSize++;
			}
			names.clear();
		}

		std::list<name> outputList;
		outputList.push_back(nameMap.begin()->first);

		auto rValue = nameMap.end();
		auto lValue = nameMap.end();
		name previous = nameMap.begin()->second;

		while ((rValue = backMap.find(*outputList.begin())) != backMap.end())
		{
			outputList.push_front(rValue->second);
		}
		while ((lValue = nameMap.find(previous)) != nameMap.end())
		{
			previous = lValue->second;
			outputList.push_back(lValue->second);
		}

		std::cout << "Front: " << outputList.front() << "   Back: " << previous << std::endl;
	}
	else
	{
		std::cout << "File not found." << std::endl;
	}
}