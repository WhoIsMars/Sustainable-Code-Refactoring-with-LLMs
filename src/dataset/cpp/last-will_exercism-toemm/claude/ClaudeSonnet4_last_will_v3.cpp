// Enter your code below the lines of the families' information

// Secret knowledge of the Zhang family:
namespace zhang {
constexpr int bank_number_part(int secret_modifier) noexcept {
    constexpr int zhang_part{8541};
    return (zhang_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() noexcept { return 512; }
}  // namespace red
namespace blue {
constexpr int code_fragment() noexcept { return 677; }
}  // namespace blue
}  // namespace zhang

// Secret knowledge of the Khan family:
namespace khan {
constexpr int bank_number_part(int secret_modifier) noexcept {
    constexpr int khan_part{4142};
    return (khan_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() noexcept { return 148; }
}  // namespace red
namespace blue {
constexpr int code_fragment() noexcept { return 875; }
}  // namespace blue
}  // namespace khan

// Secret knowledge of the Garcia family:
namespace garcia {
constexpr int bank_number_part(int secret_modifier) noexcept {
    constexpr int garcia_part{4023};
    return (garcia_part * secret_modifier) % 10000;
}
namespace red {
constexpr int code_fragment() noexcept { return 118; }
}  // namespace red
namespace blue {
constexpr int code_fragment() noexcept { return 923; }
}  // namespace blue
}  // namespace garcia

// Enter your code below
namespace estate_executor {
    constexpr int assemble_account_number(int secret_modifier) noexcept {
        constexpr int combined_part = 8541 + 4142 + 4023;
        return (combined_part * secret_modifier) % 10000;
    }

    constexpr int assemble_code() noexcept {
        constexpr int blue_sum = 677 + 875 + 923;
        constexpr int red_sum = 512 + 148 + 118;
        return blue_sum * red_sum;
    }
}