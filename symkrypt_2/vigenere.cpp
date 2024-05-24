#include "vigenere.hpp"

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
