# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple

Local = namedtuple('Local', ('dict', 'date', 'number'))


class LedgerEntry:  # Reduced object creation overhead
    __slots__ = ('date', 'description', 'change')  # Minimize memory footprint

    def __init__(self, date=None, description=None, change=None):
        self.date = date
        self.description = description
        self.change = change


def create_entry(date, description, change):
    # Direct instantiation, avoids intermediate object
    return LedgerEntry(datetime.strptime(date, '%Y-%m-%d'), description, change)


def number(pos, neg, sep):
    def wrapped(amount, currency):
        abs_amount = abs(amount)
        units, change = divmod(abs_amount, 100)
        fmt_str = pos if amount >= 0 else neg
        unit_str = str(units)
        formatted_units = sep.join(unit_str[max(0, i - 3):i] for i in range(len(unit_str), 0, -3))
        return fmt_str.format(currency, formatted_units, change)

    return wrapped


def format_entries(currency, locale, entries):
    localization = {
        'en_US': Local(
            {"Date": "Date", "Description": "Description", "Change": "Change"},
            lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',  # f-string
            number('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')),
        'nl_NL': Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',  # f-string
            number('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.'))
    }
    symbols = {"USD": "$", "EUR": "€"}
    config = localization[locale]
    header = "{Date:10s} | {Description:25s} | {Change:13s}".format(**config.dict)
    table = [header]  # Initialize table with header

    sorted_entries = sorted(entries, key=lambda e: (e.date, e.change, e.description))

    for entry in sorted_entries:
        desc = entry.description
        desc_display = desc if len(desc) <= 25 else desc[:22] + '...'
        formatted_line = '{:s} | {:<25s} | {:>13s}'.format(
            config.date(entry.date.day, entry.date.month, entry.date.year),
            desc_display,
            config.number(entry.change, symbols[currency]))
        table.append(formatted_line)

    return '\n'.join(table)