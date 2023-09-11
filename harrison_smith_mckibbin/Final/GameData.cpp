#include "GameData.h"
#include <fstream>
#include <iostream>

void FileData::loadData(const string& filename)
{
	Key tempKey;
	string tempData;

	ifstream fileToRead;
	fileToRead.open(filename, ios::in);

	if (fileToRead.is_open())
	{
		while (getline(fileToRead, tempKey, ' '))
		{
			getline(fileToRead, tempData, '\n');
			if (tempKey[0] != '#')
			{
				mData[tempKey] = tempData;
			}
		}
	}

	fileToRead.close();
}

int FileData::getIntData(const Key& key)
{
	return stoi(mData[key]);
}

float FileData::getFloatData(const Key& key)
{
	return stof(mData[key]);
}

string FileData::getStringData(const Key& key)
{
	return mData[key];
}
