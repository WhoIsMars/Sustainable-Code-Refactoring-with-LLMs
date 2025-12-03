#include "rna_transcription.h"
#include <unordered_map>

char transcription::to_rna(char ch)
{
	static const std::unordered_map<char, char> rna_map = {
		{'C', 'G'}, {'G', 'C'}, {'A', 'U'}, {'T', 'A'}
	};
	auto it = rna_map.find(ch);
	return it != rna_map.end() ? it->second : '\0';
}

std::string transcription::to_rna(std::string s)
{
	for (char &ch : s) {
		ch = to_rna(ch);
	}
	return s;
}