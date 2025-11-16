#pragma once

#include <string>
#include <regex>

namespace bob {
    static const std::regex shout {"^[^a-z]*[A-Z][^a-z]*$"};
    static const std::regex question {"\\?[^a-z]*$"};
    static const std::regex silence {"^\\W*$"};

    static const std::string RESPONSE_EMPHATIC { 
        "Calm down, I know what I'm doing!" 
    };
    static const std::string RESPONSE_SHOUTING { "Whoa, chill out!" };
    static const std::string RESPONSE_QUESTION { "Sure." };
    static const std::string RESPONSE_SILENCE  { "Fine. Be that way!" };
    static const std::string RESPONSE_DEFAULT  { "Whatever." };
    
    auto hey(const std::string&) noexcept -> std::string;
}  // namespace bob

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif