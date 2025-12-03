# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    return ([int(part) for part in date.split("-")], description, change)


def format_entries(currency, locale, entries):
    symbols = {"USD": "$", "EUR": u"€"}
    symbol = symbols.get(currency, "")

    locale_settings = {
        "en_US": {
            "header": ("Date", "Description", "Change"),
            "date_fmt": "{1:02}/{2:02}/{0}",
            "number_po_fmt": "{}{} ",
            "number_ne_fmt": "({}{})",
            "thousands": ",",
            "decimal": ".",
        },
        "nl_NL": {
            "header": ("Datum", "Omschrijving", "Verandering"),
            "date_fmt": "{2:02}-{1:02}-{0}",
            "number_po_fmt": "{} {} ",
            "number_ne_fmt": "{} -{} ",
            "thousands": ".",
            "decimal": ",",
        },
    }
    settings = locale_settings.get(locale, locale_settings["en_US"])

    ret = ["{:<11}| {:<26}| {:<13}".format(*settings["header"])]
    date_fmt = settings["date_fmt"]
    number_po_fmt = settings["number_po_fmt"]
    number_ne_fmt = settings["number_ne_fmt"]
    thousands = settings["thousands"]
    decimal = settings["decimal"]

    for date, description, change in sorted(entries):
        date = date_fmt.format(*date)
        description = description[:22] + "... " if len(description) > 25 else description
        change_abs = f"{abs(change) / 100:,.2f}".replace(",", "X").replace(".", decimal).replace("X", thousands)
        change = (number_ne_fmt if change < 0 else number_po_fmt).format(symbol, change_abs)
        ret.append("{:<11}| {:<26}| {:>13}".format(date, description, change))

    return "\n".join(ret)