# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple

Local = namedtuple('Local', ('dict', 'date_format', 'number_format'))


class LedgerEntry(object):
    __slots__ = ('date', 'description', 'change')

    def __init__(self, date=None, description=None, change=None):
        self.date = date
        self.description = description
        self.change = change


def create_entry(date, description, change):
    return LedgerEntry(datetime.strptime(date, '%Y-%m-%d'), description, change)


def number(pos, neg, sep):
    def wrapped(amount, currency):
        abs_amount = abs(amount)
        units, cents = divmod(abs_amount, 100)
        units_str = str(units)
        formatted_units = ''
        for i, digit in enumerate(reversed(units_str)):
            if i > 0 and i % 3 == 0:
                formatted_units = sep + formatted_units
            formatted_units = digit + formatted_units

        fmt_str = pos if amount >= 0 else neg
        return fmt_str.format(currency, formatted_units, cents)

    return wrapped


def format_entries(currency, locale, entries):
    localization = {
        'en_US': Local(
            {"Date": "Date", "Description": "Description", "Change": "Change"},
            '{:02d}/{:02d}/{:04d}'.format,
            number('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')),
        'nl_NL': Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            '{:02d}-{:02d}-{:04d}'.format,
            number('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.'))
    }
    symbols = {"USD": "$", "EUR": "€"}
    config = localization[locale]
    header = "{Date:10s} | {Description:25s} | {Change:13s}".format(**config.dict)
    table = [header]
    currency_symbol = symbols[currency]

    for entry in sorted(entries, key=lambda e: (e.date, e.change, e.description)):
        desc = entry.description
        if len(desc) > 25:
            desc = desc[:22] + '...'
        date_str = config.date_format(entry.date.month, entry.date.day, entry.date.year)
        change_str = config.number_format(entry.change, currency_symbol)
        table.append(f'{date_str:10s} | {desc:<25s} | {change_str:>13s}')

    return '\n'.join(table)