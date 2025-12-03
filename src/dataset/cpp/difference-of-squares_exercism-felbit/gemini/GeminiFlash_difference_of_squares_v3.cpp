namespace squares {

    unsigned long long int square_of_sum(const int n)
    {
        unsigned long long int sum = static_cast<unsigned long long int>(n) * (n + 1) / 2;
        return sum * sum;
    }

    unsigned long long int sum_of_squares(const int n)
    {
        unsigned long long int sum = static_cast<unsigned long long int>(n) * (n + 1) * (2 * n + 1) / 6;
        return sum;
    }

    unsigned long long int difference(const int n)
    {
        unsigned long long int sum_of_squares_val = static_cast<unsigned long long int>(n) * (n + 1) * (2 * n + 1) / 6;
        unsigned long long int sum = static_cast<unsigned long long int>(n) * (n + 1) / 2;
        return sum * sum - sum_of_squares_val;
    }

}