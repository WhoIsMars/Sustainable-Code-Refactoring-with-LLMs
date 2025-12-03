import threading


class BankAccount:
    def __init__(self):
        self._is_open = False
        self._balance = 0
        self._lock = threading.Lock()

    def get_balance(self):
        with self._lock:
            if not self._is_open:
                raise ValueError(".+")
            return self._balance

    def open(self):
        with self._lock:
            if self._is_open:
                raise ValueError(".+")
            self._is_open = True
            self._balance = 0

    def deposit(self, amount):
        with self._lock:
            if not self._is_open or amount <= 0:
                raise ValueError(".+")
            self._balance += amount

    def withdraw(self, amount):
        with self._lock:
            if not self._is_open or amount <= 0 or amount > self._balance:
                raise ValueError(".+")
            self._balance -= amount

    def close(self):
        with self._lock:
            if not self._is_open:
                raise ValueError(".+")
            self._is_open = False