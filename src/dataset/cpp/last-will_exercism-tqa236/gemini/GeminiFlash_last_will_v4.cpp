// Enter your code below the lines of the families' information

// Secret knowledge of the Zhang family:
namespace zhang {
    constexpr int zhang_part = 8'541;
    inline int bank_number_part(int secret_modifier) {
        return (zhang_part*secret_modifier) % 10000;
    }
    namespace red {
        constexpr int red_code = 512;
        inline int code_fragment() {return red_code;}
    }
    namespace blue {
        constexpr int blue_code = 677;
        inline int code_fragment() {return blue_code;}
    }
}

// Secret knowledge of the Khan family:
namespace khan {
    constexpr int khan_part = 4'142;
    inline int bank_number_part(int secret_modifier) {
        return (khan_part*secret_modifier) % 10000;
    }
    namespace red {
        constexpr int red_code = 148;
        inline int code_fragment() {return red_code;}
    }
    namespace blue {
        constexpr int blue_code = 875;
        inline int code_fragment() {return blue_code;}
    }
}

// Secret knowledge of the Garcia family:
namespace garcia {
    constexpr int garcia_part = 4'023;
    inline int bank_number_part(int secret_modifier) {
        return (garcia_part*secret_modifier) % 10000;
    }
    namespace red {
        constexpr int red_code = 118;
        inline int code_fragment() {return red_code;}
    }
    namespace blue {
        constexpr int blue_code = 923;
        inline int code_fragment() {return blue_code;}
    }
}

// Enter your code below

namespace estate_executor {
    inline int assemble_account_number(int secret_modifier){
        return zhang::bank_number_part(secret_modifier) + khan::bank_number_part(secret_modifier) + garcia::bank_number_part(secret_modifier);
    }

    inline int assemble_code(){
        constexpr int red_code = zhang::red::code_fragment() + khan::red::code_fragment() + garcia::red::code_fragment();
        constexpr int blue_code = zhang::blue::code_fragment() + khan::blue::code_fragment() + garcia::blue::code_fragment();
        return red_code * blue_code;
    }
}