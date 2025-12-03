# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple


Local = namedtuple('Local', ('dict', 'date', 'number'))


class LedgerEntry:
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
        units, change = divmod(abs(amount), 100)
        
        if units == 0:
            formatted_units = '0'
        else:
            digits = str(units)
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


LOCALIZATION = {
    'en_US': Local(
        {"Date": "Date", "Description": "Description", "Change": "Change"},
        lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',
        number('{}{}.{:02d} ', '({}{}.{:02d})', ',')),
    'nl_NL': Local(
        {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
        lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',
        number('{} {},{:02d} ', '{} -{},{:02d} ', '.'))
}

SYMBOLS = {"USD": "$", "EUR": "€"}


def format_entries(currency, locale, entries):
    config = LOCALIZATION[locale]
    symbol = SYMBOLS[currency]
    
    table = [f"{config.dict['Date']:10s} | {config.dict['Description']:25s} | {config.dict['Change']:13s}"]
    
    sorted_entries = sorted(entries, key=lambda e: (e.date, e.change, e.description))
    
    for entry in sorted_entries:
        desc = entry.description if len(entry.description) <= 25 else entry.description[:22] + '...'
        date_str = config.date(entry.date.day, entry.date.month, entry.date.year)
        amount_str = config.number(entry.change, symbol)
        
        table.append(f'{date_str} | {desc:<25s} | {amount_str:>13s}')
    
    return '\n'.join(table)