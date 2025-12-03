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
    return LedgerEntry(
        date=datetime.strptime(date, '%Y-%m-%d'),
        description=description,
        change=change
    )


def number(pos, neg, sep):
    def wrapped(amount, currency):
        fmt_str = pos if amount >= 0 else neg
        abs_amount = abs(amount)
        units, change = divmod(abs_amount, 100)
        digits = str(units)[::-1]
        grouped = sep.join(digits[i:i + 3] for i in range(0, len(digits), 3))[::-1]
        return fmt_str.format(currency, grouped, change)
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
    header = f"{config.dict['Date']:10s} | {config.dict['Description']:25s} | {config.dict['Change']:13s}"
    rows = [
        f"{config.date(entry.date.day, entry.date.month, entry.date.year)} | "
        f"{(entry.description[:22] + '...') if len(entry.description) > 25 else entry.description:<25s} | "
        f"{config.number(entry.change, symbols[currency]):>13s}"
        for entry in sorted(entries, key=lambda e: (e.date, e.change, e.description))
    ]
    return '\n'.join([header] + rows)