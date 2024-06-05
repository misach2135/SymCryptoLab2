#include "vigenere.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

bool VigenereLab::isLetter(char c)
{
	return (c >= char(192)) && (c <= char(255));
}

bool VigenereLab::isSmallLetter(char c)
{
	return (c >= char(224)) && (c <= char(255));
}

char VigenereLab::alphabetAdd(char a, char b)
{
	if (!isSmallLetter(a) && !isSmallLetter(b)) return ERROR_CHAR;

	char a_num = a - char(224);
	char b_num = b - char(224);

	char res = char(224) + ((a_num + b_num) % 32);

	return res;
}

char VigenereLab::alphabetSubstract(char a, char b)
{
	if (!isSmallLetter(b)) return ERROR_CHAR;

	char reversed_b = 2 * char(224) - b + 32; // Повний запис: char(224) + 32 - (b - char(224)).
											  // Таким чином знаходимо обернений до б за додаванням

	return alphabetAdd(a, reversed_b);

}

std::map<char, int> VigenereLab::getFrequency(const std::string& text) {
	std::map<char, int> frequency;
	for (char c : text) {
		if (frequency.find(c) == frequency.end())
		{
			frequency[c] = 0;
		}
		frequency[c]++;
	}
	return frequency;
}

std::string VigenereLab::Cipher(const std::string& text, const std::string& key) {
	std::string result;
	for (size_t i = 0; i < text.size(); i++) {
		char c = alphabetAdd(text[i], key[i % key.size()]);
		result += c;
	}
	return result;
}

std::string VigenereLab::Decipher(const std::string& cipher, const std::string& key) {
	std::string result;
	for (size_t i = 0; i < cipher.size(); i++) {
		char c = alphabetSubstract(cipher[i], key[i % key.size()]);
		result += c;
	}
	return result;
}

std::string VigenereLab::ParseText(std::ifstream& in)
{
	std::string res;
	char c = '\0';
	while (in.get(c))
	{
		if (isLetter(c))
		{
			c = tolower(c);
			res += c;
		}
	}
	return res;
}

std::vector<std::string> VigenereLab::ParseKeys(std::ifstream& in)
{
	std::vector<std::string> keys;
	char c = 0;
	std::string key = "";
	in >> std::noskipws;
	while (in.get(c))
	{
		if (isLetter(c))
		{
			key += c;
		}
		if (c == '\n' || in.peek() == EOF)
		{
			keys.push_back(key);
			key = "";
		}
	}
	return keys;
}

std::vector<std::string> VigenereLab::CipherTexts(const std::string& text, const std::vector<std::string>& keys, std::ofstream& out)
{
	std::vector<std::string> cipheredTexts;
	out << "CIPHER: " << std::endl;
	for (int i = 0; i < keys.size(); i++)
	{
		out << "Key " << i << ": " << keys[i] << std::endl;
		cipheredTexts.push_back(Cipher(text, keys[i]));
		out << cipheredTexts.back() << std::endl;
	}
	return cipheredTexts;
}

void VigenereLab::DecipherTexts(const std::vector<std::string>& cipheredTexts, const std::vector<std::string>& keys, std::ofstream& out)
{
	out << "DECIPHER: " << std::endl;
	for (int i = 0; i < keys.size(); i++)
	{
		out << "Key " << i << ": " << keys[i] << std::endl;
		out << Decipher(cipheredTexts[i], keys[i]) << std::endl;
	}
}

double VigenereLab::CalcConfIndex(const std::string& text)
{
	double I = 0;
	auto freqMap = getFrequency(text);
	for (char c = char(224); c != char(255); c++)
	{
		auto e = freqMap.find(c);
		if (e != freqMap.end())
		{
			I += e->second * (e->second - 1);
		}
	}
	I /= (static_cast<double>(text.size()) * (text.size() - 1));
	return I;
}

double VigenereLab::GetConfIndexOfLang()
{
	double I = 0;

	for (auto e : FREQ_TABLE)
	{
		I += e.second * e.second;
	}

	return I;

}

// This bullshit does not work! Or maybe work, but i am stupid
// Працює, але не дуже зручно. Залишу це тут як згадку про невігластво.
int VigenereLab::TryQuizLength1(std::string& text, int maxLength, double I)
{
	double I0 = static_cast<double>(1) / 32;
	double min = 0;
	std::ofstream out("QuizingTest.txt");
	if (!out.is_open()) return 0;

	out << "I0 = " << I0 << std::endl;

	for (int r = 2; r < maxLength; r++)
	{
		std::vector<double> coefIndexes;
		for (int i = 0; i < r; i++)
		{
			auto subtxt = GetIthBlock(text, r, i);
			coefIndexes.push_back(CalcConfIndex(subtxt));
		}

		out << "r = " << r << std::endl;
		out << "Coefs: ";

		double Ir = 0;

		for (auto e : coefIndexes)
		{
			Ir += e;
			//out << e << ", ";
		}

		Ir /= coefIndexes.size();

		out << abs(Ir - I0 ) << std::endl;

		out << std::endl;
		out << std::endl;

	}

	return 0;
}

// Good student, good. I will give you bowl of rice! +200 marks on campus
int VigenereLab::TryQuizLength2(std::string& text, int maxLength, double epsilon)
{
	int maxIndex = 0;
	double maxD = 0;
	for (int r = 6; r < maxLength; r++)
	{
		int D = 0;
		for (int i = 0; i < int64_t(text.size()) - r; i++)
		{
			D += text[i] == text[i + r];
		}
		// std::cout << "R = " << r << ": " << D << std::endl;
		if (D > maxD)
		{
			maxD = D;
			maxIndex = r;
		}

	}

	std::cout << std::endl;

	return maxIndex;

}


std::string VigenereLab::GetIthBlock(const std::string& text, int blockSize, int i)
{
	std::string res;

	for (int j = i; j < text.size(); j += blockSize)
	{
		res.push_back(text[j]);
	}

	return res;
}

std::string VigenereLab::CeasarVigenreCracker(const std::string& text, int blockSize)
{
	std::map<char, double> langFreqsPr(FREQ_TABLE);
	std::string key;
	auto langGreatest  = GetMaxPairFromMap(FREQ_TABLE);

	for (int i = 0; i < blockSize; i++)
	{
		std::map<char, int> blockFreqs = getFrequency(GetIthBlock(text, blockSize, i));

		auto blockGreatest = GetMaxPairFromMap(blockFreqs);


		key.push_back(alphabetSubstract(blockGreatest.first, langGreatest.first));

	}

	return key;
}

std::string VigenereLab::CrackVigenere(std::string& text, int blockSize)
{
	std::string key;
	for (int i = 0; i < blockSize; i++)
	{
		std::map<char, double> m;
		auto block = GetIthBlock(text, blockSize, i);
		auto blockFreqs = getFrequency(block);

		for (const auto& g : FREQ_TABLE)
		{
			double Mg = 0;
			for (const auto& t : FREQ_TABLE)
			{
				char tg = alphabetAdd(t.first, g.first);
				if (blockFreqs.find(tg) == blockFreqs.end()) continue;
				Mg += t.second * blockFreqs[tg];
			}
			m[g.first] = Mg;
		}

		auto maxElement = GetMaxPairFromMap(m);
		key.push_back(maxElement.first);
	}

	return key;
}


