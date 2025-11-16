// Enter your code below the lines of the families' information

// Secret knowledge of the Zhang family:
namespace zhang {
    inline int bank_number_part(int secret_modifier) {
        constexpr int zhang_part{8'541};
        return (zhang_part*secret_modifier) % 10000;
    }
    namespace red {
        inline int code_fragment() {return 512;}
    }
    namespace blue {
        inline int code_fragment() {return 677;}
    }
}

// Secret knowledge of the Khan family:
namespace khan {
    inline int bank_number_part(int secret_modifier) {
        constexpr int khan_part{4'142};
        return (khan_part*secret_modifier) % 10000;
    }
    namespace red {
        inline int code_fragment() {return 148;}
    }
    namespace blue {
        inline int code_fragment() {return 875;}
    }
}

// Secret knowledge of the Garcia family:
namespace garcia {
    inline int bank_number_part(int secret_modifier) {
        constexpr int garcia_part{4'023};
        return (garcia_part*secret_modifier) % 10000;
    }
    namespace red {
        inline int code_fragment() {return 118;}
    }
    namespace blue {
        inline int code_fragment() {return 923;}
    }
}

// Enter your code below
namespace estate_executor {
  inline int assemble_account_number(int secret_modifier) {
    return zhang::bank_number_part(secret_modifier) + 
            khan::bank_number_part(secret_modifier) + 
            garcia::bank_number_part(secret_modifier);
  }

  inline int assemble_code() {
    constexpr int red_sum = zhang::red::code_fragment() +
                            khan::red::code_fragment() +
                            garcia::red::code_fragment();
    constexpr int blue_sum = zhang::blue::code_fragment() +
                             khan::blue::code_fragment() +
                             garcia::blue::code_fragment();
    return red_sum * blue_sum;
  }
}