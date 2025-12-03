# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    return (tuple(int(x) for x in date.split("-", 2)), description, change)


def format_entries(currency, locale, entries):
    # Pre-compute locale-specific configurations
    config = {
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
    
    cfg = config[(currency, locale)]
    
    ret = ["{:<11}| {:<26}| {:<13}".format(*cfg["header"])]
    
    for date, description, change in sorted(entries):
        date_str = cfg["date_fmt"].format(*date)
        
        desc_str = description if len(description) <= 25 else description[:22] + "... "
        
        change_abs = abs(change) / 100
        change_str = f"{change_abs:.2f}".replace(".", cfg["decimal"])
        
        # Add thousands separators
        if len(change_str) > 6:
            parts = change_str.split(cfg["decimal"])
            integer_part = parts[0]
            decimal_part = parts[1] if len(parts) > 1 else ""
            
            # Insert thousands separators from right to left
            if len(integer_part) > 3:
                formatted_int = ""
                for i, digit in enumerate(reversed(integer_part)):
                    if i > 0 and i % 3 == 0:
                        formatted_int = cfg["thousands"] + formatted_int
                    formatted_int = digit + formatted_int
                change_str = formatted_int + (cfg["decimal"] + decimal_part if decimal_part else "")
        
        change_formatted = (cfg["number_ne_fmt"] if change < 0 else cfg["number_po_fmt"]).format(cfg["symbol"], change_str)
        
        ret.append("{:<11}| {:<26}| {:>13}".format(date_str, desc_str, change_formatted))
    
    return "\n".join(ret)