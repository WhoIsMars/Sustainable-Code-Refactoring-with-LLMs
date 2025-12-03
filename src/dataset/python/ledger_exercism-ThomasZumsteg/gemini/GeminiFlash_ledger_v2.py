# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple


Local = namedtuple('Local', ('dict', 'date_format', 'number_format'))


class LedgerEntry(object):
    def __init__(self, date, description, change):
        self.date = date
        self.description = description
        self.change = change


def create_entry(date_str, description, change):
    date = datetime.strptime(date_str, '%Y-%m-%d').date()
    return LedgerEntry(date, description, change)

def number_format(pos, neg, sep):
    def wrapped(amount, currency):
        fmt_str = pos if amount >= 0 else neg
        abs_amount = abs(amount)
        units, cents = divmod(abs_amount, 100)
        
        unit_str = str(units)
        parts = []
        for i in range(len(unit_str) - 1, -1, -3):
            parts.append(unit_str[max(0, i - 2):i + 1])
        
        formatted_units = sep.join(reversed(parts))
        return fmt_str.format(currency, formatted_units, cents)
    return wrapped

def format_entries(currency, locale, entries):
    localization = {
        'en_US':  Local(
             {"Date": "Date", "Description": "Description", "Change": "Change"},
            '{:02d}/{:02d}/{:04d}'.format,
            number_format('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')),
        'nl_NL': Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            '{:02d}-{:02d}-{:04d}'.format,
            number_format('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.'))
    }
    symbols = {"USD": "$", "EUR": "€"}
    config = localization[locale]
    header = "{Date:10s} | {Description:25s} | {Change:13s}".format(**config.dict)
    table = [header]

    formatted_entries = []
    for entry in sorted(entries, key=lambda e: (e.date, e.change, e.description)):
        desc = entry.description
        if len(desc) > 25:
            desc = desc[:22] + '...'
        
        date_str = config.date_format(entry.date.month, entry.date.day, entry.date.year)
        change_str = config.number_format(entry.change, symbols[currency])
        formatted_entries.append('{:s} | {:<25s} | {:>13s}'.format(date_str, desc, change_str))

    return '\n'.join(table + formatted_entries)