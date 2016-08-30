#include "Bimap.h"

void Bimap::performParsing(std::string filein)
{
	const std::string filepath = filein;
	const char parsingChar = ',';
	std::ifstream file;
	map nameMap;
	int maxSize = 0;

	file.open(filepath, std::ifstream::in);
	if (file.is_open())
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			name currName;
			std::vector<std::string> names;
			std::istringstream strStream(line);
			while (std::getline(strStream, currName, parsingChar))
			{
				names.push_back(currName);
			}
			if (names.size() > 0)
			{
				name lWord = names.at(0), rWord = names.at(1);
				nameMap.insert(values(lWord, rWord));
				maxSize++;
			}
		}

		std::list<std::string> outputList;
		outputList.push_back(nameMap.begin()->left);
		name previous = nameMap.begin()->right;

		auto lEnd = nameMap.right.end();
		auto left = nameMap.right.end();
		auto rEnd = nameMap.left.end();
		auto right = nameMap.left.end();

		while ((left = nameMap.right.find(*outputList.begin())) != lEnd)
		{
			outputList.push_front(left->get_left());
		}

		while ((right = nameMap.left.find(previous)) != rEnd)
		{
			name sRight = right->get_right();
			previous = sRight;
			outputList.push_back(sRight);
		}

		std::cout << "Front: " << outputList.front() << "   Back: " << previous << std::endl;
	}
	else
	{
		std::cout << "File not found." << std::endl;
	}
}