// Secret knowledge of the Zhang family:
namespace zhang {
    int bank_number_part(int secret_modifier) {
        int zhang_part{8'541};
        return (zhang_part*secret_modifier) % 10000;
    }
    namespace red {
        int code_fragment() {return 512;}
    }
    namespace blue {
        int code_fragment() {return 677;}
    }
}

// Secret knowledge of the Khan family:
namespace khan {
    int bank_number_part(int secret_modifier) {
        int khan_part{4'142};
        return (khan_part*secret_modifier) % 10000;
    }
    namespace red {
        int code_fragment() {return 148;}
    }
    namespace blue {
        int code_fragment() {return 875;}
    }
}

// Secret knowledge of the Garcia family:
namespace garcia {
    int bank_number_part(int secret_modifier) {
        int garcia_part{4'023};
        return (garcia_part*secret_modifier) % 10000;
    }
    namespace red {
        int code_fragment() {return 118;}
    }
    namespace blue {
        int code_fragment() {return 923;}
    }
}

// ## 1. Take your seat in front of the families and lay out your papers
namespace estate_executor {
// ## 2. Find the secret account number
    int assemble_account_number(int secret_modifier) {
        const int zhangs  {zhang::bank_number_part(secret_modifier)};
        const int khans   {khan::bank_number_part(secret_modifier)};
        const int garcias {garcia::bank_number_part(secret_modifier)};
        return zhangs + khans + garcias;
    }
// ## 3. Last step: Enter the secret code
    int assemble_code() {
        int blues {0}, reds {0};

        blues += zhang::blue::code_fragment();
        reds  += zhang::red::code_fragment();
        blues += khan::blue::code_fragment();
        reds  += khan::red::code_fragment();
        blues += garcia::blue::code_fragment();
        reds  += garcia::red::code_fragment();

        return blues * reds;
    }
} // namespace estate_executor



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif