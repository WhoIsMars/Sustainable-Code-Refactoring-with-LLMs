import threading


class BankAccount:
    def __init__(self):
        self._is_open = False
        self._balance = 0
        self._lock = threading.Lock()

    def get_balance(self):
        with self._lock:
            if not self._is_open:
                raise ValueError("Account not open")
            return self._balance

    def open(self):
        with self._lock:
            if self._is_open:
                raise ValueError("Account already open")
            self._is_open = True
            self._balance = 0

    def deposit(self, amount):
        with self._lock:
            if not self._is_open:
                raise ValueError("Account not open")
            if amount <= 0:
                raise ValueError("Cannot deposit non-positive amount")
            self._balance += amount

    def withdraw(self, amount):
        with self._lock:
            if not self._is_open:
                raise ValueError("Account not open")
            if amount <= 0:
                raise ValueError("Cannot withdraw non-positive amount")
            if amount > self._balance:
                raise ValueError("Insufficient funds")
            self._balance -= amount

    def close(self):
        with self._lock:
            if not self._is_open:
                raise ValueError("Account not open")
            self._is_open = False