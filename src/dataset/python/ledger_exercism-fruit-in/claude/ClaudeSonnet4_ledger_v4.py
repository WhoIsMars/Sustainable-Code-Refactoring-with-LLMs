# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    return (tuple(int(x) for x in date.split("-")), description, change)


def format_entries(currency, locale, entries):
    # Pre-compute locale-specific configurations
    configs = {
        ("USD", "en_US"): {
            "symbol": "$",
            "header": ("Date", "Description", "Change"),
            "date_fmt": "{1:02}/{2:02}/{0}",
            "number_po_fmt": "{}{} ",
            "number_ne_fmt": "({}{})",
            "thousands": ",",
            "decimal": "."
        },
        ("EUR", "en_US"): {
            "symbol": "€",
            "header": ("Date", "Description", "Change"),
            "date_fmt": "{1:02}/{2:02}/{0}",
            "number_po_fmt": "{}{} ",
            "number_ne_fmt": "({}{})",
            "thousands": ",",
            "decimal": "."
        },
        ("USD", "nl_NL"): {
            "symbol": "$",
            "header": ("Datum", "Omschrijving", "Verandering"),
            "date_fmt": "{2:02}-{1:02}-{0}",
            "number_po_fmt": "{} {} ",
            "number_ne_fmt": "{} -{} ",
            "thousands": ".",
            "decimal": ","
        },
        ("EUR", "nl_NL"): {
            "symbol": "€",
            "header": ("Datum", "Omschrijving", "Verandering"),
            "date_fmt": "{2:02}-{1:02}-{0}",
            "number_po_fmt": "{} {} ",
            "number_ne_fmt": "{} -{} ",
            "thousands": ".",
            "decimal": ","
        }
    }
    
    config = configs[(currency, locale)]
    
    ret = ["{:<11}| {:<26}| {:<13}".format(*config["header"])]
    
    for date, description, change in sorted(entries):
        date_str = config["date_fmt"].format(*date)
        
        if len(description) > 25:
            description = description[:22] + "... "
        
        change_abs = f"{abs(change) / 100:.2f}".replace(".", config["decimal"])
        
        # Add thousands separators more efficiently
        if len(change_abs) > 6:
            parts = []
            start = len(change_abs) - 3
            while start > 3:
                parts.append(change_abs[start:start+3])
                start -= 3
            parts.append(change_abs[:start+3])
            change_abs = config["thousands"].join(reversed(parts))
        
        number_fmt = config["number_ne_fmt"] if change < 0 else config["number_po_fmt"]
        change_str = number_fmt.format(config["symbol"], change_abs)
        
        ret.append(f"{date_str:<11}| {description:<26}| {change_str:>13}")
    
    return "\n".join(ret)