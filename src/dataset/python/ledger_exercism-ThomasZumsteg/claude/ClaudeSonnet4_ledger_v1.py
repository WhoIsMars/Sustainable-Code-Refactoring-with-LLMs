# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple


Local = namedtuple('Local', ('dict', 'date', 'number'))


class LedgerEntry(object):
    __slots__ = ('date', 'description', 'change')
    
    def __init__(self):
        self.date = None
        self.description = None
        self.change = None


def create_entry(date, description, change):
    entry = LedgerEntry()
    entry.date = datetime.strptime(date, '%Y-%m-%d')
    entry.description = description
    entry.change = change
    return entry

def number(pos, neg, sep):
    def wrapped(amount, currency):
        fmt_str = pos if amount >= 0 else neg 
        abs_amount = abs(amount)
        units, change = divmod(abs_amount, 100)
        
        if units == 0:
            formatted_units = '0'
        else:
            digits = str(units)
            if len(digits) <= 3:
                formatted_units = digits
            else:
                # Group digits by 3 from right to left
                groups = []
                for i in range(len(digits), 0, -3):
                    groups.append(digits[max(0, i-3):i])
                formatted_units = sep.join(reversed(groups))
        
        return fmt_str.format(currency, formatted_units, change)
    return wrapped

# Pre-compute localization data
_LOCALIZATION = {
    'en_US': Local(
        {"Date": "Date", "Description": "Description", "Change": "Change"},
        lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',
        number('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')),
    'nl_NL': Local(
        {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
        lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',
        number('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.'))
}

_SYMBOLS = {"USD": "$", "EUR": "€"}

def format_entries(currency, locale, entries):
    config = _LOCALIZATION[locale]
    symbol = _SYMBOLS[currency]
    
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