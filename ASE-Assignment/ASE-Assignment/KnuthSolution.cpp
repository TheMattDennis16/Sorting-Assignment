#include "KnuthSolution.h"

KnuthSolution::KnuthSolution(std::string file)
{
	filename = file;
}

void KnuthSolution::solve()
{
	fileCopy fileF = readFile(filename);
	fileCopy fileH = swapKeyValue(fileF);
	fileCopy fileG;
	fileF.sort();
	fileH.sort();

	fileCopy newFileF;
	fileCopy newFileG = fileG;

	auto it = fileF.begin();
	auto hit = fileH.begin();

	while (it != fileF.end() && hit != fileH.end())
	{
		if (it->first == hit->first)
		{
			newFileF.push_back(std::pair<name, name>(it->second, hit->second));
		}
		else if (it->first > hit->first)
		{
			newFileG.push_back(std::pair<name, name>(std::to_string(fileF.size()), hit->first));
			newFileG.push_back(std::pair<name, name>(std::to_string(fileF.size() - 1), hit->second));
			it--;
		}
		else if (it->first < hit->first)
		{
			//newFileG.push_back(std::pair<name, name>(std::to_string((int)it->first.c_str()), it->first));
			hit--;
		}
		hit++;
		it++;
	}

	fileF = newFileF;
	fileH = fileF;
	fileF = swapKeyValue(fileF);
	fileF.sort();
	fileH.sort();
	fileG = newFileG;

	bool finished = false;
	int t = 2;
	int originalSize = fileF.size();

	std::cout << "Original Size: " << originalSize << std::endl;

	while (!fileF.empty())
	{
		auto fPair = fileF.begin();
		auto hPair = fileH.begin();
		auto gPair = fileG.begin();
		fileCopy fileF1;
		fileCopy fileG1;

		while (fPair != fileF.end() && *fPair != std::pair<name, name>("",""))
		{
			std::cout << "FileF: " << fPair->first << ":" << fPair->second << " FileH: " << hPair->first << ":" << hPair->second << " FileG: " << gPair->first << ":" << gPair->second << std::endl;
			if (fPair->second == hPair->first)
			{
				fileF1.push_back(std::pair<name, name>(fPair->first, hPair->second));
				fPair++;
				advanceIterator(hPair, fileH);
			}
 			if (fPair->second == gPair->second)
			{
				std::pair<name, name> newPair(std::to_string(std::stoi(gPair->first) - t), fPair->first);
				fileG1.push_back(newPair);
				fPair++;
				//advanceIterator(gPair, fileG);	
				std::pair<name, name> copyPair(gPair->first, gPair->second);
				auto copyIt = gPair;
				gPair++;
				if (gPair == fileG.end() || *copyIt == std::pair<name, name>("", ""))
				{
					std::cout << "Resetting size: " << fileG.size() << " it" << std::endl;
					gPair = fileG.begin()++;
				}
				else
				{
					gPair++;
					std::cout << "Advancing size: " << fileG.size() << " it" << std::endl;
				}
			}
			if (fPair->second > gPair->second)
			{
				auto copyIt = gPair;
				if (copyIt++ == fileG.end() || *copyIt == std::pair<name, name>("", ""))
				{
					std::cout << "Resetting size: " << fileG.size() << " it" << std::endl;
					gPair = fileG.begin();
				}
				else
				{
					gPair++;
					std::cout << "Advancing size: " << fileG.size() << " it" << std::endl;
				}
				//advanceIterator(gPair, fileG);
			}
			if (fPair->second > hPair->first)
			{
				advanceIterator(hPair, fileH);
			}
		}
		t *= 2;
		fileF = fileF1;
		fileG1 = swapKeyValue(fileG1);
		fileG1.sort();
		fileG1 = swapKeyValue(fileG1);
		fileG.merge(fileG1);
		std::cout << "t = " << t << std::endl;
	}
	fileG = swapKeyValue(fileG);
	std::cout << "First: " << atIndex(fileG, 0).first << "   Last: " << atIndex(fileG, fileG.size()-1).second << std::endl;
}

fileCopy KnuthSolution::readFile(std::string fileIn)
{
	const char parsingChar = ',';
	std::ifstream file;
	fileCopy nameMap;

	file.open(fileIn, std::ifstream::in);
	if (file.is_open())
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			name currName;
			std::vector<name> names;
			std::istringstream strStream(line);
			while (std::getline(strStream, currName, parsingChar))
			{
				names.push_back(currName);
			}
			if (names.size() > 0)
			{
				nameMap.push_back(std::pair<name, name>(names[0], names[1]));
			}
		}
	}
	return nameMap;
}

fileCopy KnuthSolution::swapKeyValue(fileCopy & original)
{
	fileCopy out;
	for (auto pair : original)
	{
		out.push_back(std::pair<std::string, std::string>(pair.second, pair.first));
	}
	return out;
}

std::pair<name, name> KnuthSolution::atIndex(fileCopy & container, int index)
{
	if (index > container.size())
	{
		return std::pair<name, name>();
	}

	fileCopy::iterator it = container.begin();
	for (int i = 0; i < index; i++)
		it++;
	//std::advance(it, index);
	return *it;
}

std::pair<name,name> find(fileCopy& file, name value)
{
	std::pair<name, name> ret;
	auto it = file.begin();
	while (it != file.end())
	{
		if (it->second == value)
		{
			ret = *it;
			break;
		}
	}
	return ret;
}

void KnuthSolution::writeToFile(fileCopy& file, std::string fileNameToWrite)
{
	std::ofstream fileOut;
	fileOut.open(fileNameToWrite, std::ios::out);
	if (fileOut.is_open())
	{
		for (auto& pair : file)
		{
			fileOut << pair.first << "," << pair.second << std::endl;
		}
	}
	fileOut.close();
}