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
        
        # Add thousands separators more efficiently
        if len(change_abs) > 6:
            parts = []
            integer_part = change_abs[:-3]  # Everything except .XX
            decimal_part = change_abs[-3:]  # .XX part
            
            # Process integer part from right to left
            for i in range(len(integer_part), 0, -3):
                start = max(0, i - 3)
                parts.append(integer_part[start:i])
            
            change_abs = config['thousands'].join(reversed(parts)) + decimal_part
        
        number_fmt = config['number_ne_fmt'] if change < 0 else config['number_po_fmt']
        change_str = number_fmt.format(symbol, change_abs)
        
        ret.append("{:<11}| {:<26}| {:>13}".format(date_str, description, change_str))
    
    return "\n".join(ret)