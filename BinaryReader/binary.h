#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <wrl\client.h>
#include <algorithm>

class BinaryOps
{
private:
	std::vector<UINT16> testvector;
	std::ofstream output;
	std::ifstream input;

public:
	BinaryOps()
	{
		output.open("binary.kkt", std::ios::binary | std::ios::out);
	}

	~BinaryOps()
	{
		input.close();
	}

	void run()
	{
		BinaryOps::FillOutput();
		BinaryOps::LoadInput();
	}
private:
	void FillOutput()
	{
		testvector.push_back(6036);
		testvector.push_back(2);
		testvector.push_back(255);
		testvector.push_back(15);
		testvector.push_back(2);
		testvector.push_back(1);
		testvector.push_back(9);
		testvector.push_back(3);
		testvector.push_back(5);
		testvector.push_back(17);
		testvector.push_back(0);

		output.write((const char*) testvector.data(), testvector.size() * sizeof(UINT16));
		output.close();
	}

	void LoadInput()
	{
		input.open("binary.kkt", std::ios::binary);
		if (!input.is_open())
		{
			std::cout << "Unable to open file" << std::endl;
			return;
		}
		input.seekg(0, input.end);
		int bufferVectorSize = input.tellg();
		input.seekg(0, input.beg);
		std::vector <UINT16> bufferVector(bufferVectorSize / sizeof(UINT16));
		input.read((char*)bufferVector.data(), bufferVectorSize);
		DecompressFrame(bufferVector);
	}

	void DecompressFrame(std::vector<UINT16> bufferVector)
	{
		std::vector<int> finalVector(bufferVector[0]);
		std::vector<int>::iterator pos = finalVector.begin();
		int val;
		
		for (int i{ 1 }; i < bufferVector.size(); i += 2)
		{
			val = bufferVector[i+1];
			std::fill(pos, pos + bufferVector[i], val);
			pos += bufferVector[i];
		}

		for (int i{ 0 }; i < finalVector.size(); i++)
			std::cout << finalVector[i] << " ";
		std::cout << std::endl;
	}
};