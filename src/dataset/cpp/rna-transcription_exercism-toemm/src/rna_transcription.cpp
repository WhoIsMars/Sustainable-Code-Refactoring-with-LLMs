#include "rna_transcription.h"

#include <map>

namespace rna_transcription {




std::string to_rna(std::string dna) {

    std::string rna{};


    for (char c : dna) {
        rna += to_rna(c);
    }

    return rna;


}

char to_rna(char dna) {

    std::map<char, char> encoding {{'G', 'C'},
                                    {'C', 'G'},
                                    {'T', 'A'},
                                    {'A', 'U'}};

    return encoding[dna];
}

}  // namespace rna_transcription
