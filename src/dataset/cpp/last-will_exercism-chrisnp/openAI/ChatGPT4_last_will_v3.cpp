namespace zhang {
    constexpr int bank_number_part(int secret_modifier) {
        return (8'541 * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 512; }
    }
    namespace blue {
        constexpr int code_fragment() { return 677; }
    }
}

namespace khan {
    constexpr int bank_number_part(int secret_modifier) {
        return (4'142 * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 148; }
    }
    namespace blue {
        constexpr int code_fragment() { return 875; }
    }
}

namespace garcia {
    constexpr int bank_number_part(int secret_modifier) {
        return (4'023 * secret_modifier) % 10000;
    }
    namespace red {
        constexpr int code_fragment() { return 118; }
    }
    namespace blue {
        constexpr int code_fragment() { return 923; }
    }
}

namespace estate_executor {
    constexpr int assemble_account_number(int secret_modifier) {
        return zhang::bank_number_part(secret_modifier) +
               khan::bank_number_part(secret_modifier) +
               garcia::bank_number_part(secret_modifier);
    }

    constexpr int assemble_code() {
        constexpr int blues = zhang::blue::code_fragment() +
                              khan::blue::code_fragment() +
                              garcia::blue::code_fragment();
        constexpr int reds = zhang::red::code_fragment() +
                             khan::red::code_fragment() +
                             garcia::red::code_fragment();
        return blues * reds;
    }
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif