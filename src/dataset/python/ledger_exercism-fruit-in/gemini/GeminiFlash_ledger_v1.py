# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    year, month, day = map(int, date.split("-"))
    return ([year, month, day], description, change)


def format_entries(currency, locale, entries):
    if currency == "USD":
        symbol = "$"
    elif currency == "EUR":
        symbol = "€"  # Use the actual Euro symbol directly

    if locale == "en_US":
        header = ("Date", "Description", "Change")
        date_fmt = "{1:02}/{2:02}/{0}"
        number_po_fmt = "{}{} "
        number_ne_fmt = "({}{})"
        thousands = ","
        decimal = "."
    elif locale == "nl_NL":
        header = ("Datum", "Omschrijving", "Verandering")
        date_fmt = "{2:02}-{1:02}-{0}"
        number_po_fmt = "{} {} "
        number_ne_fmt = "{} -{} "
        thousands = "."
        decimal = ","
    else:
        raise ValueError(f"Unsupported locale: {locale}")

    ret = ["{:<11}| {:<26}| {:<13}".format(*header)]

    for date, description, change in sorted(entries):
        date = date_fmt.format(*date)
        description = description[:22] + "... " if len(description) > 25 else description

        change_abs = abs(change) / 100
        change_abs_str = "{:.2f}".format(change_abs)
        change_abs_str = change_abs_str.replace(".", decimal)

        parts = list(change_abs_str)
        for i in range(len(parts) - 6, 0, -3):
            parts.insert(i, thousands)
        change_abs_str = "".join(parts)

        number_fmt = number_ne_fmt if change < 0 else number_po_fmt
        change_str = number_fmt.format(symbol, change_abs_str)

        ret.append("{:<11}| {:<26}| {:>13}".format(date, description, change_str))

    return "\n".join(ret)