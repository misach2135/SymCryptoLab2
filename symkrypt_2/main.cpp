#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <algorithm>

#include "vigenere.hpp"

// Частоти символів знайдені у лабораторній 1

void lab()
{
	using namespace VigenereLab;
	std::ifstream inText("text.txt");
	std::ifstream inKeys("keys.txt");
	std::ifstream inVariant("variant.txt");

	std::ofstream outCiphered("ciphered.txt");
	std::ofstream outUnciphered("unciphered.txt");
	std::ofstream outUncipheredVariant("uncipheredVariant.txt");

	if (!inText.is_open() || !inKeys.is_open())
	{
		std::cout << "Error! File is not opened! Check filename" << std::endl;
		exit(0);
		return;
	}

	std::string text = ParseText(inText);
	std::string variantText = ParseText(inVariant);
	std::vector<std::string> keys = ParseKeys(inKeys);

	auto ciphTexts = CipherTexts(text, keys, outCiphered);
	std::vector<double> ConfIndexesCipherTexts;

	std::cout << "Conf index of input: " << CalcConfIndex(text) << std::endl;

	for (const auto& e : ciphTexts)
	{
		ConfIndexesCipherTexts.push_back(CalcConfIndex(e));
		std::cout << ConfIndexesCipherTexts.back() << ", ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	DecipherTexts(ciphTexts, keys, outUnciphered);

	std::cout << TryQuizLength1(variantText, 30, GetConfIndexOfLang()) << std::endl; // Довжина блоку-- 20 символів.
	std::cout << TryQuizLength2(variantText, 30, GetConfIndexOfLang()) << std::endl; // Довжина блоку-- 20 символів.

	auto key1 = CeasarVigenreCracker(variantText, 20);
	auto key2 = CrackVigenere(variantText, 20);

	std::cout << "CeasarVigenreCracker: " << key1 << std::endl;
	std::cout << "CrackVigenere: " << key2 << std::endl;

	outUncipheredVariant << Decipher(variantText, key2);
}

int main()
{
	// We will use WIN-1251 CP
	setlocale(LC_ALL, "ru-Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	lab();

	return 0;
}
 