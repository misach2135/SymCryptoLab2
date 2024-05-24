#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>

#include "vigenere.hpp"

// Частоти символів знайдені у лабораторній 1

void part1()
{
	using namespace VigenereLab;
	std::ifstream inText("text.txt");
	std::ifstream inKeys("keys.txt");

	std::ofstream outCiphered("ciphered.txt");
	std::ofstream outUnciphered("unciphered.txt");

	if (!inText.is_open() || !inKeys.is_open())
	{
		std::cout << "Error! File is not opened! Check filename" << std::endl;
		exit(0);
		return;
	}

	std::string text = ParseText(inText);
	std::vector<std::string> keys = ParseKeys(inKeys);

	auto ciphTexts = CipherTexts(text, keys, outCiphered);

	for (const auto& e : ciphTexts)
	{
		std::cout << CalcConfIndex(e) << ", ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	DecipherTexts(ciphTexts, keys, outUnciphered);
}

int main()
{
	// We will use WIN-1251 CP
	setlocale(LC_ALL, "ru-Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	part1();


	return 0;
}
