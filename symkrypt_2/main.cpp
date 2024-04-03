#include <iostream>
#include <vector>
#include <map>

std::map<char, int> getFrequency(const std::string& text) {
    std::map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }
    return frequency;
}

std::string Cipher(const std::string& text, const std::string& key) {
    std::string result;
    for (size_t i = 0; i < text.size(); i++) {
        char c = (text[i] + key[i % key.size()]) % 32;
        result += c;
    }
    return result;
}

std::string Decipher(const std::string& cipherText, const std::string& key) {
    std::string result;
    for (size_t i = 0; i < cipherText.size(); i++) {
        char c = (cipherText[i] - key[i % key.size()] + 32) % 32;
        result += c;
    }
    return result;
}

int main() {
    std::string text = "блять, придумать чет нада ";
    std::vector<std::string> keys = { "1", "2", "3", "4", "5" };

    // почтак шифрування
    std::vector<std::string> cipherTexts;
    for (const std::string& key : keys) {
        cipherTexts.push_back(vigenereCipher(text, key));
    }

    std::map<char, int> textFrequency = getFrequency(text);
    for (const std::string& cipherText : cipherTexts) {
        std::map<char, int> cipherTextFrequency = getFrequency(cipherText);
        // дописати обчислення індексів
    }

    std::string decipheredText = vigenereDecipher(cipherTexts[0], keys[0]);
    // рахувати якось довжину ключа

    return 0;
}
