#include "food_chain.h"

namespace {
    
    struct verses {
        verses(const std::string& food, const std::string& reaction, const std::string& verse)
            : food_(food), reaction_(reaction), verse_(verse) {}

        std::string sing() const {
            return "I know an old lady who swallowed a " + food_ + ".\n" + reaction_ + verse_;
        }

        std::string verse() const {
            return verse_;
        }

    private:
        std::string food_;
        std::string reaction_;
        std::string verse_;
    };

    verses const the_verses[] = {
        {
            "fly",
            "",
            "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        },
        {
            "spider",
            "It wriggled and jiggled and tickled inside her.\n",
            "She swallowed the spider to catch the fly.\n"
        },
        {
            "bird",
            "How absurd to swallow a bird!\n",
            "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        },
        {
            "cat",
            "Imagine that, to swallow a cat!\n",
            "She swallowed the cat to catch the bird.\n"
        },
        {
            "dog",
            "What a hog, to swallow a dog!\n",
            "She swallowed the dog to catch the cat.\n"
        },
        {
            "goat",
            "Just opened her throat and swallowed a goat!\n",
            "She swallowed the goat to catch the dog.\n"
        },
        {
            "cow",
            "I don't know how she swallowed a cow!\n",
            "She swallowed the cow to catch the goat.\n"
        },
        {
            "horse",
            "",
            "She's dead, of course!\n"
        }
    };

    const size_t num_verses = sizeof(the_verses)/sizeof(the_verses[0]);
}

std::string
food_chain::verse(size_t num)
{
    if (num > 0 && num <= num_verses) {
        std::string song = the_verses[--num].sing();
        if (num < num_verses - 1) {
            while (num--) {
                song += the_verses[num].verse();
            }
        }

        return song;
    }

    return std::string();
}

std::string
food_chain::verses(size_t start, size_t end)
{
    std::string song;

    for (size_t v = start; v <= end; ++v) {
        song += verse(v) + "\n";
    }

    return song;
}

std::string food_chain::sing()
{
    return verses(1, num_verses);
}

