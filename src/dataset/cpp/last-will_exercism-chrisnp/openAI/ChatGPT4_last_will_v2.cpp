// Secret knowledge of the Zhang family:
namespace zhang {
    constexpr int bank_number_part(int secret_modifier) {
        constexpr int zhang_part{8'541};
        return (zhang_part * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 512; }
    }
    namespace blue {
        constexpr int code_fragment() { return 677; }
    }
}

// Secret knowledge of the Khan family:
namespace khan {
    constexpr int bank_number_part(int secret_modifier) {
        constexpr int khan_part{4'142};
        return (khan_part * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 148; }
    }
    namespace blue {
        constexpr int code_fragment() { return 875; }
    }
}

// Secret knowledge of the Garcia family:
namespace garcia {
    constexpr int bank_number_part(int secret_modifier) {
        constexpr int garcia_part{4'023};
        return (garcia_part * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 118; }
    }
    namespace blue {
        constexpr int code_fragment() { return 923; }
    }
}

// ## 1. Take your seat in front of the families and lay out your papers
namespace estate_executor {
// ## 2. Find the secret account number
    constexpr int assemble_account_number(int secret_modifier) {
        return zhang::bank_number_part(secret_modifier) +
               khan::bank_number_part(secret_modifier) +
               garcia::bank_number_part(secret_modifier);
    }
// ## 3. Last step: Enter the secret code
    constexpr int assemble_code() {
        constexpr int blues = zhang::blue::code_fragment() +
                              khan::blue::code_fragment() +
                              garcia::blue::code_fragment();
        constexpr int reds = zhang::red::code_fragment() +
                             khan::red::code_fragment() +
                             garcia::red::code_fragment();
        return blues * reds;
    }
} // namespace estate_executor

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif