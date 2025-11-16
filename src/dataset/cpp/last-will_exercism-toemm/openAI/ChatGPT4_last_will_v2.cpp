namespace zhang {
constexpr int bank_number_part(int secret_modifier) {
    constexpr int zhang_part{8'541};
    return (zhang_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() { return 512; }
}  // namespace red
namespace blue {
constexpr int code_fragment() { return 677; }
}  // namespace blue
}  // namespace zhang

namespace khan {
constexpr int bank_number_part(int secret_modifier) {
    constexpr int khan_part{4'142};
    return (khan_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() { return 148; }
}  // namespace red
namespace blue {
constexpr int code_fragment() { return 875; }
}  // namespace blue
}  // namespace khan

namespace garcia {
constexpr int bank_number_part(int secret_modifier) {
    constexpr int garcia_part{4'023};
    return (garcia_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() { return 118; }
}  // namespace red
namespace blue {
constexpr int code_fragment() { return 923; }
}  // namespace blue
}  // namespace garcia

namespace estate_executor {
    constexpr int assemble_account_number(int secret_modifier) {
        return zhang::bank_number_part(secret_modifier) + khan::bank_number_part(secret_modifier) + 
               garcia::bank_number_part(secret_modifier);
    }

    constexpr int assemble_code() {
        constexpr int blue_sum = zhang::blue::code_fragment() + khan::blue::code_fragment() + garcia::blue::code_fragment();
        constexpr int red_sum = zhang::red::code_fragment() + khan::red::code_fragment() + garcia::red::code_fragment();
        return blue_sum * red_sum;
    }
}