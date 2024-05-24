#ifndef VIGENERELAB_HPP
#define VIGENERELAB_HPP

#include <map>
#include <vector>
#include <string>
#include <fstream>


namespace VigenereLab
{
	const char ERROR_CHAR = '\0';
	const std::map<char, double> FREQ_TABLE =
	{
		{'�', 0.0697201},
		{'�', 0.0172286},
		{'�', 0.056724},
		{'�', 0.0213469},
		{'�', 0.0324454},
		{'�', 0.0858417},
		{'�', 0.00986348},
		{'�', 0.0162057},
		{'�', 0.0879848},
		{'�', 0.0114292},
		{'�', 0.0311624},
		{'�', 0.0499457},
		{'�', 0.0361014},
		{'�', 0.0651102},
		{'�', 0.104177},
		{'�', 0.0195504},
		{'�', 0.0443487},
		{'�', 0.0633102},
		{'�', 0.0510155},
		{'�', 0.0256018},
		{'�', 0.000955243},
		{'�', 0.0115707},
		{'�', 0.00528456},
		{'�', 0.00954003},
		{'�', 0.00566461},
		{'�', 0.00225927},
		{'�', 0.000411046},
		{'�', 0.0182337},
		{'�', 0.0155054},
		{'�', 0.000103772},
		{'�', 0.00895783},
		{'�', 0.0224008}
	};

	bool isLetter(char c);

	bool isSmallLetter(char c);

	char alphabetAdd(char a, char b);

	char alphabetSubstract(char a, char b);

	std::map<char, int> getFrequency(const std::string& text);

	std::string Cipher(const std::string& text, const std::string& key);

	std::string Decipher(const std::string& cipher, const std::string& key);

	std::string ParseText(std::ifstream& in);

	std::vector<std::string> ParseKeys(std::ifstream& in);

	std::vector<std::string> CipherTexts(const std::string& text, const std::vector<std::string>& keys, std::ofstream& out);

	void DecipherTexts(const std::vector<std::string>& cipheredTexts, const std::vector<std::string>& keys, std::ofstream& out);

	double CalcConfIndex(const std::string& text);
}

#endif