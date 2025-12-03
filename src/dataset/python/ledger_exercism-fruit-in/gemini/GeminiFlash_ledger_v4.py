# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    return (tuple(map(int, date.split("-"))), description, change)


def format_entries(currency, locale, entries):
    if currency == "USD":
        symbol = "$"
    elif currency == "EUR":
        symbol = "€"
    else:
        symbol = currency  # Handle unknown currencies gracefully

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
    else:  # Provide a default locale
        header = ("Date", "Description", "Change")
        date_fmt = "{1:02}/{2:02}/{0}"
        number_po_fmt = "{}{} "
        number_ne_fmt = "({}{})"
        thousands = ","
        decimal = "."

    ret = ["{:<11}| {:<26}| {:<13}".format(*header)]

    for date, description, change in sorted(entries):
        date = date_fmt.format(*date)
        description = (description[:22] + "...") if len(description) > 25 else description
        change_abs = f"{abs(change) / 100:.2f}".replace(".", decimal)
        
        parts = list(change_abs)
        for i in range(len(parts) - 6, 0, -3):
            parts.insert(i, thousands)
        change_abs = "".join(parts)

        number_fmt = number_ne_fmt if change < 0 else number_po_fmt
        change = number_fmt.format(symbol, change_abs)

        ret.append("{:<11}| {:<26}| {:>13}".format(date, description, change))

    return "\n".join(ret)