#include "robot_name.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace robot_name;

static std::mt19937 mersenne_twister_engine{std::random_device{}()};
static std::uniform_int_distribution<> letter_distribution(0, 25);
static std::uniform_int_distribution<> number_distribution(0, 9);

string robot::gen_letters()
{
    return string(1, static_cast<char>(letter_distribution(mersenne_twister_engine) + 65));
}

string robot::gen_numbers()
{
    return to_string(number_distribution(mersenne_twister_engine));
}

string robot::make_name()
{
    string current;
    current.reserve(5);
    current += gen_letters();
    current += gen_letters();
    current += gen_numbers();
    current += gen_numbers();
    current += gen_numbers();

    return current;
}

string robot::name() const
{
    return final_name;
}

void robot::reset()
{
    final_name = make_name();
}

robot::robot() : final_name(make_name())
{
    cout << final_name << endl;
}