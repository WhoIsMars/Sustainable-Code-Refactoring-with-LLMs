#pragma once

#include <string>
#include <vector>

namespace protein_translation {

typedef std::string codon;
typedef std::string polypeptide;
typedef std::string ARN;

std::vector<polypeptide> proteins(const ARN&);

}  // namespace protein_translation
