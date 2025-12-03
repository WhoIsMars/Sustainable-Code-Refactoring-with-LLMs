# -*- coding: utf-8 -*-


def create_entry(date, description, change):
    return (tuple(int(x) for x in date.split("-")), description, change)


def format_entries(currency, locale, entries):
    # Pre-compute locale-specific configurations
    if locale == "en_US":
        config = {
            'header': ("Date", "Description", "Change"),
            'date_fmt': "{1:02}/{2:02}/{0}",
            'number_po_fmt': "{}{} ",
            'number_ne_fmt': "({}{})",
            'thousands': ",",
            'decimal': "."
        }
    else:  # nl_NL
        config = {
            'header': ("Datum", "Omschrijving", "Verandering"),
            'date_fmt': "{2:02}-{1:02}-{0}",
            'number_po_fmt': "{} {} ",
            'number_ne_fmt': "{} -{} ",
            'thousands': ".",
            'decimal': ","
        }
    
    symbol = "$" if currency == "USD" else "€"
    
    ret = ["{:<11}| {:<26}| {:<13}".format(*config['header'])]
    
    for date, description, change in sorted(entries):
        date_str = config['date_fmt'].format(*date)
        
        if len(description) > 25:
            description = description[:22] + "... "
        
        change_abs = "{:.2f}".format(abs(change) / 100)
        if config['decimal'] != ".":
            change_abs = change_abs.replace(".", config['decimal'])
        
        # Add thousands separators
        parts = change_abs.split(config['decimal'])
        integer_part = parts[0]
        if len(integer_part) > 3:
            formatted_integer = ""
            for i, digit in enumerate(reversed(integer_part)):
                if i > 0 and i % 3 == 0:
                    formatted_integer = config['thousands'] + formatted_integer
                formatted_integer = digit + formatted_integer
            change_abs = formatted_integer + config['decimal'] + parts[1]
        
        number_fmt = config['number_ne_fmt'] if change < 0 else config['number_po_fmt']
        change_str = number_fmt.format(symbol, change_abs)
        
        ret.append("{:<11}| {:<26}| {:>13}".format(date_str, description, change_str))
    
    return "\n".join(ret)