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
		{'à', 0.0697201},
		{'á', 0.0172286},
		{'â', 0.056724},
		{'ã', 0.0213469},
		{'ä', 0.0324454},
		{'å', 0.0858417},
		{'æ', 0.00986348},
		{'ç', 0.0162057},
		{'è', 0.0879848},
		{'é', 0.0114292},
		{'ê', 0.0311624},
		{'ë', 0.0499457},
		{'ì', 0.0361014},
		{'í', 0.0651102},
		{'î', 0.104177},
		{'ï', 0.0195504},
		{'ð', 0.0443487},
		{'ñ', 0.0633102},
		{'ò', 0.0510155},
		{'ó', 0.0256018},
		{'ô', 0.000955243},
		{'õ', 0.0115707},
		{'ö', 0.00528456},
		{'÷', 0.00954003},
		{'ø', 0.00566461},
		{'ù', 0.00225927},
		{'ú', 0.000411046},
		{'û', 0.0182337},
		{'ü', 0.0155054},
		{'ý', 0.000103772},
		{'þ', 0.00895783},
		{'ÿ', 0.0224008}
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