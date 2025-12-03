namespace squares {

    unsigned long long int square_of_sum(const int n)
    {
        // Use arithmetic series formula: sum = n(n+1)/2
        const unsigned long long int sum = static_cast<unsigned long long int>(n) * (n + 1) / 2;
        return sum * sum;
    }

    unsigned long long int sum_of_squares(const int n)
    {
        // Use formula: sum of squares = n(n+1)(2n+1)/6
        const unsigned long long int n_ull = static_cast<unsigned long long int>(n);
        return n_ull * (n_ull + 1) * (2 * n_ull + 1) / 6;
    }

    unsigned long long int difference(const int n)
    {
        return square_of_sum(n) - sum_of_squares(n);
    }

}