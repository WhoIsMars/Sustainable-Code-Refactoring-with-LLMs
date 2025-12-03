# -*- coding: utf-8 -*-
from datetime import datetime
from collections import namedtuple


Local = namedtuple('Local', ('dict', 'date', 'number'))


class LedgerEntry:
    __slots__ = ('date', 'description', 'change')

    def __init__(self, date=None, description=None, change=None):
        self.date = date
        self.description = description
        self.change = change


def create_entry(date, description, change):
    return LedgerEntry(
        date=datetime.strptime(date, '%Y-%m-%d'),
        description=description,
        change=change
    )


def number(pos, neg, sep):
    def wrapped(amount, currency):
        fmt_str = pos if amount >= 0 else neg
        units, change = divmod(abs(amount), 100)
        digits = f"{units:,}".replace(",", sep)
        return fmt_str.format(currency, digits, change)
    return wrapped


def format_entries(currency, locale, entries):
    localization = {
        'en_US': Local(
            {"Date": "Date", "Description": "Description", "Change": "Change"},
            lambda day, month, year: f'{month:02d}/{day:02d}/{year:04d}',
            number('{}{:s}.{:02d} ', '({}{:s}.{:02d})', ',')
        ),
        'nl_NL': Local(
            {"Date": "Datum", "Description": "Omschrijving", "Change": "Verandering"},
            lambda day, month, year: f'{day:02d}-{month:02d}-{year:04d}',
            number('{} {:s},{:02d} ', '{} -{:s},{:02d} ', '.')
        )
    }
    symbols = {"USD": "$", "EUR": "€"}
    config = localization[locale]

    # Generate Header Row
    table = [f"{config.dict['Date']:10s} | {config.dict['Description']:25s} | {config.dict['Change']:13s}"]

    # Sort entries once and reuse
    sorted_entries = sorted(entries, key=lambda e: (e.date, e.change, e.description))

    for entry in sorted_entries:
        desc = entry.description
        table.append(f"{config.date(entry.date.day, entry.date.month, entry.date.year)} | "
                     f"{desc[:25]:<25s} | "
                     f"{config.number(entry.change, symbols[currency]):>13s}")
    return '\n'.join(table)