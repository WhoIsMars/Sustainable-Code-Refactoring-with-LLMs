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
        units_str = str(units)
        formatted_units = sep.join(reversed([units_str[i:i+3] for i in range(0, len(units_str), 3)]))
        return fmt_str.format(currency, formatted_units[::-1], change)
    return wrapped

def format_entries(currency, locale, entries):
    localization = {
        'en_US':  Local(
             {"Date": "Date", "Description": "Description", "Change": "Change"},
            lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',
            number('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')),
        'nl_NL': Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',
            number('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.'))
    }
    symbols = {"USD": "$", "EUR": "€"}
    config = localization[locale]
    header = "{Date:10s} | {Description:25s} | {Change:13s}".format(**config.dict)
    table = [header]
    currency_symbol = symbols[currency]
    for entry in sorted(entries, key=lambda e: (e.date, e.change, e.description)):
        desc = entry.description
        desc = desc[:22] + '...' if len(desc) > 25 else desc
        formatted_date = config.date(entry.date.day, entry.date.month, entry.date.year)
        formatted_change = config.number(entry.change, currency_symbol)
        table.append(f'{formatted_date} | {desc:<25s} | {formatted_change:>13s}')

    return '\n'.join(table)