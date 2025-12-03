import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {

    private static final String WITHDRAWING_TOO_MUCH = "Cannot withdraw more money than is currently in the account";
    private static final String EMPTY_ACCOUNT = "Cannot withdraw money from an empty account";
    private static final String NEGATIVE_AMOUNT = "Cannot deposit or withdraw negative amount";
    private static final String ACCOUNT_CLOSED = "Account closed";
    private int account;
    private boolean open;
    private final Lock lock = new ReentrantLock();

    public void open() {
        lock.lock();
        try {
            this.open = true;
        } finally {
            lock.unlock();
        }
    }

    public void close() {
        lock.lock();
        try {
            this.open = false;
        } finally {
            lock.unlock();
        }
    }

    public int getBalance() throws BankAccountActionInvalidException {
        lock.lock();
        try {
            checkIfAccountIsClosed(open);
            return this.account;
        } finally {
            lock.unlock();
        }
    }

    public void deposit(int amount) throws BankAccountActionInvalidException {
        lock.lock();
        try {
            checkIfAccountIsClosed(open);
            checkForNegativeAmount(amount);
            this.account += amount;
        } finally {
            lock.unlock();
        }
    }

    public void withdraw(int amount) throws BankAccountActionInvalidException {
        lock.lock();
        try {
            checkIfAccountIsClosed(open);
            checkForNegativeAmount(amount);
            checkIfAccountIsZero(account);
            checkIfWithdrawingTooMuch(account, amount);
            this.account -= amount;
        } finally {
            lock.unlock();
        }
    }

    private void checkIfWithdrawingTooMuch(int account, int amount)
            throws BankAccountActionInvalidException {
        if (account - amount < 0) {
            throw new BankAccountActionInvalidException(WITHDRAWING_TOO_MUCH);
        }
    }

    private void checkIfAccountIsZero(int account)
            throws BankAccountActionInvalidException {
        if (account == 0) {
            throw new BankAccountActionInvalidException(EMPTY_ACCOUNT);
        }
    }

    private void checkForNegativeAmount(int amount)
            throws BankAccountActionInvalidException {
        if (amount < 0) {
            throw new BankAccountActionInvalidException(NEGATIVE_AMOUNT);
        }
    }

    private void checkIfAccountIsClosed(boolean open)
            throws BankAccountActionInvalidException {
        if (!open) {
            throw new BankAccountActionInvalidException(ACCOUNT_CLOSED);
        }
    }
}