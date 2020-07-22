Task is to implement class CTaxRegister, which implements a simple tax revenue database.

The database is very simplified. We assume the database holds information about all citizens from the moment they born until they die. Each citizen is identified by his/her account. The accounts are strings and are unique in the database. Second, citizens may be positively identified by their names and addresses. We assume the pair (name, address) is unique in the database. That is, there may exist many citizens with the same name (e.g. "John Smith"), there may be many citizens registered with the same address (e.g. "Main Street 10"), however, there may be at most one "John Smith" registered on "Main Street 10".

The class shall implement the following public interface:

    -A constructor (without parameters). This constructor initializes a new empty database.
    -Destructor -- it shall free all resources used by the instance.
    -Method Birth (Name, Addr, Acct ) which adds a new record to the database. The parameters are name, address and account id of the person being registered. The method returns true if it succeeds, or false if it fails (the pair Name, Addr is already present in the database, or the Acct is not unique in the database).
    -Method Death (Name, Addr) removes the corresponding record from the database, the record is identified by the name and address. The method returns true if it succeeds, or false if it fails (the corresponding record was not present).
    -Methods Income add Amount to the income of some account. There are two variants of the method: the account is either identified directly by account id, or the account is identified by the owner name and address. The methods return true if they succeed, or false if they fail (the corresponding person was not found).
    -Methods Expense add Amount to the expenses of some account. There are two variants of the method: the account is either identified directly by account id, or the account is identified by the owner name and address. The methods return true if they succeed, or false if they fail (the corresponding person was not found).
    -Method Audit ( Name, Addr, Acct, SumIncome, SumExpense) searches the database for the record identified by owner name and address. The method fills the Acct, SumIncome, and SumExpense output parameters accordingly. The method returns true if it succeeds, or false if it fails (the corresponding person was not found). Moreover, if the method fails, the output parameters shall be left unmodified.
    -Method ListByName creates and returns a new instance of class CIterator. The exact interface of the returned object is listed below, the object is used to access the records in the tax register. The records are visited in a sorted way, the order will be based on the person names (i.e., the person with the lexicographically smallest name is visited first). If the tax register contains two records with the same name, then the record with lexicographically smaller address goes first.

The public interface of CIterator class is the following:

    -Method AtEnd returns a boolean true if the end of the register was reached (the iterator does not refer to any valid record) or boolean false if the iterator did not reach the end of the register (it refers to a valid record).
    -Method Next which advances the iterator further.
    -Method Name to retrieve the name of a person at the current iterator position.
    -Method Addr to retrieve the address of a person at the current iterator position.
    -Method Account to retrieve the account id of a person at the current iterator position.
