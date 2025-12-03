public class BankAccount {

    private static final String WITHDRAWING_TOO_MUCH = "Cannot withdraw more money than is currently in the account";
    private static final String EMPTY_ACCOUNT = "Cannot withdraw money from an empty account";
    private static final String NEGATIVE_AMOUNT = "Cannot deposit or withdraw negative amount";
    private static final String ACCOUNT_CLOSED = "Account closed";
    
    private volatile int account;
    private volatile boolean open;

    public void open() {
        this.open = true;
    }

    public void close() {
        this.open = false;
    }

    public int getBalance() throws BankAccountActionInvalidException {
        if (!open) {
            throw new BankAccountActionInvalidException(ACCOUNT_CLOSED);
        }
        return this.account;
    }

    public synchronized void deposit(int amount) throws BankAccountActionInvalidException {
        if (!open) {
            throw new BankAccountActionInvalidException(ACCOUNT_CLOSED);
        }
        if (amount < 0) {
            throw new BankAccountActionInvalidException(NEGATIVE_AMOUNT);
        }
        this.account += amount;
    }

    public synchronized void withdraw(int amount) throws BankAccountActionInvalidException {
        if (!open) {
            throw new BankAccountActionInvalidException(ACCOUNT_CLOSED);
        }
        if (amount < 0) {
            throw new BankAccountActionInvalidException(NEGATIVE_AMOUNT);
        }
        if (account == 0) {
            throw new BankAccountActionInvalidException(EMPTY_ACCOUNT);
        }
        if (account < amount) {
            throw new BankAccountActionInvalidException(WITHDRAWING_TOO_MUCH);
        }
        this.account -= amount;
    }
}