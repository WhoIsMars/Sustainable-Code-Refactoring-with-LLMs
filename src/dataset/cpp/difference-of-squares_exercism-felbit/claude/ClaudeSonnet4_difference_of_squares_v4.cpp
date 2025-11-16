namespace squares {

    unsigned long long int square_of_sum(const int n)
    {
        const unsigned long long int sum = static_cast<unsigned long long int>(n) * (n + 1) / 2;
        return sum * sum;
    }

    unsigned long long int sum_of_squares(const int n)
    {
        return static_cast<unsigned long long int>(n) * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned long long int difference(const int n)
    {
        const unsigned long long int n_ull = static_cast<unsigned long long int>(n);
        const unsigned long long int sum = n_ull * (n + 1) / 2;
        const unsigned long long int square_sum = sum * sum;
        const unsigned long long int sum_squares = n_ull * (n + 1) * (2 * n + 1) / 6;
        return square_sum - sum_squares;
    }

}