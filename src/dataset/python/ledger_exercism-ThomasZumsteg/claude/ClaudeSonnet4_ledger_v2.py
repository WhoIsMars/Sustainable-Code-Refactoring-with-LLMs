# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple


Local = namedtuple('Local', ('dict', 'date', 'number'))


class LedgerEntry(object):
    __slots__ = ('date', 'description', 'change')
    
    def __init__(self, date, description, change):
        self.date = datetime.strptime(date, '%Y-%m-%d')
        self.description = description
        self.change = change


def create_entry(date, description, change):
    return LedgerEntry(date, description, change)

def number(pos, neg, sep):
    def wrapped(amount, currency):
        fmt_str = pos if amount >= 0 else neg 
        abs_amount = abs(amount)
        units, change = divmod(abs_amount, 100)
        digits = str(units)
        
        # Format thousands separator more efficiently
        if len(digits) <= 3:
            formatted_units = digits
        else:
            parts = []
            for i in range(len(digits), 0, -3):
                start = max(0, i - 3)
                parts.append(digits[start:i])
            formatted_units = sep.join(parts)
        
        return fmt_str.format(currency, formatted_units, change)
    return wrapped

def format_entries(currency, locale, entries):
    # Pre-compute localization data
    if locale == 'en_US':
        config = Local(
            {"Date": "Date", "Description": "Description", "Change": "Change"},
            lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',
            number('{}{}.{:02d} ', '({}{}.{:02d})', ','))
        symbol = "$" if currency == "USD" else "€"
    else:  # nl_NL
        config = Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',
            number('{} {},{:02d} ', '{} -{},{:02d} ', '.'))
        symbol = "$" if currency == "USD" else "€"
    
    # Generate Header Row
    table = [f"{config.dict['Date']:10s} | {config.dict['Description']:25s} | {config.dict['Change']:13s}"]
    
    # Sort entries once
    sorted_entries = sorted(entries, key=lambda e: (e.date, e.change, e.description))
    
    for entry in sorted_entries:
        desc = entry.description
        if len(desc) > 25:
            desc = desc[:22] + '...'
        
        date_str = config.date(entry.date.day, entry.date.month, entry.date.year)
        amount_str = config.number(entry.change, symbol)
        
        table.append(f'{date_str} | {desc:<25s} | {amount_str:>13s}')
    
    return '\n'.join(table)