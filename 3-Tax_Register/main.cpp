#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>

using namespace std;

class CTaxRegister;

class CIterator;

struct lessThanKeyNA;

struct lessThanKeyId;
/**
 * The class is used to access the records in the tax register. 
 * The records are visited in a sorted way, the order will be based on the person names.
 * 
 * @method AtEnd 
 *    returns a boolean true if the end of the register was reached.
 * @param void
 * @return false if the iterator did not reach the end of the register
 *         true if the end of the register was reached
 * 
 * @method Next 
 *    which advances the iterator further.
 * @param void
 * @return void
 * 
 * @method Name 
 *    retrieves the name of a person at the current iterator position.
 * @param void
 * @return name(String).
 * 
 * @method Addr 
 *    retrieves the address of a person at the current iterator position.
 * @param void
 * @return address(String).
 * 
 * @method Account 
 *    retrieves the account of a person at the current iterator position.
 * @param void
 * @return account(String).
 * 
 */
class CIterator
{
private:
    vector<CTaxRegister>::const_iterator it;
    size_t index;
    size_t size;

public:
    CIterator(vector<CTaxRegister>::const_iterator _it, const size_t &_size);

    bool AtEnd(void) const;
    void Next(void);

    string Name(void) const;
    string Addr(void) const;
    string Account(void) const;
};

/**
 * The class implements a simple tax revenue database.
 * The database holds information about all citizens from the moment they born until they die. 
 * Each citizen is identified by his/her account. 
 * The accounts are strings and are unique in the database.
 * Second, citizens may be positively identified by their names and addresses. 
 * The pair (name, address) is unique in the database. 
 * 
 * @method Birth 
 *    Adds a new record to the database.
 * @param name(String), addr(String) and acct(String).
 * @return returns true if it succeeds, or false if it fails
 *         (Name, Addr is already present in the database, or the Acct is not unique in the database).
 * 
 * @method Death 
 *    Removes the corresponding record from the database.
 * @param Name(String) and addr(String).
 * @return true if it succeeds, or false if it fails (the corresponding record was not present).
 * 
 * @method Income 
 *    Adds Amount to the income of some account. The account is identified directly by account id.
 * @param account(String) and amount(Int).
 * @return true if it succeeds, or false if it fails (the corresponding person was not found).
 * 
 * @method Income 
 *   Another variant of the previous method. Adds Amount to the income of some account. 
 *   The account is identified directly by name and address.
 * @param name(String), addr(String) and amount(Int).
 * @return true if it succeeds, or false if it fails (the corresponding person was not found).
 * 
 * @method Expense
 *    Adds Amount to the expenses of some account. The account is identified directly by account id.
 * @param account(String) and amount(Int).
 * @return true if they succeed, or false if they fail (the corresponding person was not found).
 * 
 * @method Expense
 *    Another variant of the previous method. Adds Amount to the expenses of some account.
 *    The account is identified by the owner name and address.
 * @param name(String), addr(String) and amount(Int).
 * @return true if they succeed, or false if they fail (the corresponding person was not found).
 * 
 * @method Audit
 *    Searches the database for the record identified by owner name and address. 
 *    The method fills the Acct, SumIncome, and SumExpense output parameters accordingly.
 * @param name(String), addr(String), account(String), sumIncome(Int) and sumExpense(Int).
 * @return true if it succeeds, or false if it fails (the corresponding person was not found).
 * 
 * @method ListByName
 *    Creates a new instance of class CIterator. The object is used to access the records in the tax register.
 * @param void.
 * @return an instance of class CIterator.
 */
class CTaxRegister
{
private:
    string m_Name;
    string m_Address;
    string m_Account;
    int m_Income;
    int m_Expense;

public:
    vector<CTaxRegister> vec;
    vector<CTaxRegister> vecId;

    string GetName() const;
    string GetAddress() const;
    string GetAccount() const;
    int GetIncome() const;
    int GetExpense() const;
    void SetName(string name);
    void SetAddress(string addr);
    void SetAccount(string account);
    void SetIncome(int income);
    void SetExpense(int expense);

    CTaxRegister();
    void printVecNA();
    void printVecId();
    bool MatchById(const string &id) const;
    bool MatchByNA(const string &name, const string &addr) const;
    bool Birth(const string &name, const string &addr, const string &account);
    bool Death(const string &name, const string &addr);
    bool Income(const string &account, int amount);
    bool Income(const string &name, const string &addr, int amount);
    bool Expense(const string &account, int amount);
    bool Expense(const string &name, const string &addr, int amount);
    bool Audit(const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const;

    CIterator ListByName(void) const;
};
/**
 * Structure to compare CTaxRegister instances in terms of adress
 */
struct lessThanKeyNA
{
    inline bool operator()(const CTaxRegister &ins1, const CTaxRegister &ins2)
    {
        if (ins1.GetName() == ins2.GetName())
        {
            return (ins1.GetAddress() < ins2.GetAddress());
        }
        else
        {
            return (ins1.GetName() < ins2.GetName());
        }
    }
};
/**
 * Structure to compare CTaxRegister instances in terms of account id
 */
struct lessThanKeyId
{
    inline bool operator()(const CTaxRegister &ins1, const CTaxRegister &ins2)
    {
        return (ins1.GetAccount() < ins2.GetAccount());
    }
};

/* Getters*/
string CTaxRegister::GetName() const
{
    return m_Name;
}

string CTaxRegister::GetAddress() const
{
    return m_Address;
}

string CTaxRegister::GetAccount() const
{
    return m_Account;
}

int CTaxRegister::GetIncome() const
{
    return m_Income;
}

int CTaxRegister::GetExpense() const
{
    return m_Expense;
}

/*Setters*/
void CTaxRegister::SetName(string name)
{
    m_Name = name;
}

void CTaxRegister::SetAddress(string addr)
{
    m_Address = addr;
}

void CTaxRegister::SetAccount(string account)
{
    m_Account = account;
}

void CTaxRegister::SetIncome(int amount)
{
    m_Income += amount;
}

void CTaxRegister::SetExpense(int expense)
{
    m_Expense += expense;
}

CTaxRegister::CTaxRegister()
{
    m_Name = "";
    m_Address = "";
    m_Account = "";
    m_Income = 0;
    m_Expense = 0;
}

void CTaxRegister::printVecNA()
{
    for (int i = 0; i < (int)vec.size(); i++)
    {
        cout << vec[i].GetName() << " " << vec[i].GetAddress() << " " << vec[i].GetAccount() << " " << vec[i].GetIncome() << " " << vec[i].GetExpense() << endl;
    }
}

void CTaxRegister::printVecId()
{
    for (int i = 0; i < (int)vecId.size(); i++)
    {
        cout << vecId[i].GetName() << " " << vecId[i].GetAddress() << " " << vecId[i].GetAccount() << " " << vecId[i].GetIncome() << " " << vecId[i].GetExpense() << endl;
    }
}

bool CTaxRegister::MatchById(const string &account) const
{
    CTaxRegister temp;
    temp.SetAccount(account);
    if (binary_search(vecId.begin(), vecId.end(), temp, lessThanKeyId()))
        return true;
    return false;
}

bool CTaxRegister::MatchByNA(const string &name, const string &addr) const
{
    CTaxRegister temp;
    temp.SetName(name);
    temp.SetAddress(addr);
    if (binary_search(vec.begin(), vec.end(), temp, lessThanKeyNA()))
        return true;
    return false;
}

bool CTaxRegister::Birth(const string &name, const string &addr, const string &account)
{
    if (MatchByNA(name, addr) == true || MatchById(account) == true)
    {
        return false;
    }
    else
    {
        CTaxRegister x;
        x.SetName(name);
        x.SetAddress(addr);
        x.SetAccount(account);

        auto where_1 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        auto where_2 = lower_bound(begin(vecId), end(vecId), x, lessThanKeyId());
        vec.insert(where_1, x);
        vecId.insert(where_2, x);

        return true;
    }
}
bool CTaxRegister::Death(const string &name, const string &addr)
{
    if (MatchByNA(name, addr))
    {
        for (int i = 0; i < (int)vec.size(); i++)
        {
            if (name == vec[i].GetName() && addr == vec[i].GetAddress())
                vec.erase(vec.begin() + i);
        }
        for (int i = 0; i < (int)vecId.size(); i++)
        {
            if (name == vecId[i].GetName() && addr == vecId[i].GetAddress())
            {
                vecId.erase(vecId.begin() + i);
                return true;
            }
        }
    }
    return false;
}
bool CTaxRegister::Income(const string &account, int amount)
{
    if (MatchById(account))
    {
        CTaxRegister x;
        x.SetAccount(account);
        auto where_1 = lower_bound(begin(vecId), end(vecId), x, lessThanKeyId());
        x.SetName(where_1->GetName());
        x.SetAddress(where_1->GetAddress());
        where_1->SetIncome(amount);
        auto where_2 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        where_2->SetIncome(amount);

        return true;
    }
    return false;
}
bool CTaxRegister::Income(const string &name, const string &addr, int amount)
{
    if (MatchByNA(name, addr))
    {
        CTaxRegister x;
        x.SetName(name);
        x.SetAddress(addr);
        auto where_1 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        where_1->SetIncome(amount);
        return true;
    }
    return false;
}
bool CTaxRegister::Expense(const string &account, int amount)
{
    if (MatchById(account))
    {
        CTaxRegister x;
        x.SetAccount(account);
        auto where_1 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        auto where_2 = lower_bound(begin(vecId), end(vecId), x, lessThanKeyId());
        where_1->SetExpense(amount);
        where_2->SetExpense(amount);
        return true;
    }
    return false;
}
bool CTaxRegister::Expense(const string &name, const string &addr, int amount)
{
    if (MatchByNA(name, addr))
    {
        CTaxRegister x;
        x.SetName(name);
        x.SetAddress(addr);
        auto where_1 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        auto where_2 = lower_bound(begin(vecId), end(vecId), x, lessThanKeyId());
        where_1->SetExpense(amount);
        where_2->SetExpense(amount);
        return true;
    }
    return false;
}

bool CTaxRegister::Audit(const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const
{
    if (MatchByNA(name, addr))
    {
        CTaxRegister x;
        x.SetName(name);
        x.SetAddress(addr);
        auto where_1 = lower_bound(begin(vec), end(vec), x, lessThanKeyNA());
        account = where_1->GetAccount();
        sumIncome = where_1->GetIncome();
        sumExpense = where_1->GetExpense();
        return true;
    }
    return false;
}

CIterator CTaxRegister::ListByName(void) const
{
    vector<CTaxRegister>::const_iterator it = vec.begin();
    return CIterator(it, vec.size());
}

CIterator::CIterator(vector<CTaxRegister>::const_iterator _it, const size_t &_size)
{
    it = _it;
    size = _size;
    index = 0;
}

bool CIterator::AtEnd(void) const
{
    if (index >= size)
        return true;
    else
        return false;
}
void CIterator::Next(void)
{
    it++;
    index++;
}

string CIterator::Name(void) const
{
    return it->GetName();
}

string CIterator::Addr(void) const
{
    return it->GetAddress();
}

string CIterator::Account(void) const
{
    return it->GetAccount();
}

int main()
{
    string acct;
    int sumIncome, sumExpense;
    CTaxRegister b1;
    assert(b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert(b1.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert(b1.Birth("Peter Hacker", "Main Street 17", "634oddT"));
    assert(b1.Birth("John Smith", "Main Street 17", "Z343rwZ"));
    assert(b1.Income("Xuj5#94", 1000));
    assert(b1.Income("634oddT", 2000));
    assert(b1.Income("123/456/789", 3000));

    assert(b1.Income("634oddT", 4000));
    assert(b1.Income("Peter Hacker", "Main Street 17", 2000));
    assert(b1.Expense("Jane Hacker", "Main Street 17", 2000));
    assert(b1.Expense("John Smith", "Main Street 17", 500));
    assert(b1.Expense("Jane Hacker", "Main Street 17", 1000));
    assert(b1.Expense("Xuj5#94", 1300));
    assert(b1.Audit("John Smith", "Oak Road 23", acct, sumIncome, sumExpense));
    assert(acct == "123/456/789");
    assert(sumIncome == 3000);
    assert(sumExpense == 0);
    assert(b1.Audit("Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert(acct == "Xuj5#94");
    assert(sumIncome == 1000);
    assert(sumExpense == 4300);
    assert(b1.Audit("Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert(acct == "634oddT");
    assert(sumIncome == 8000);
    assert(sumExpense == 0);
    assert(b1.Audit("John Smith", "Main Street 17", acct, sumIncome, sumExpense));
    assert(acct == "Z343rwZ");
    assert(sumIncome == 0);
    assert(sumExpense == 500);

    CIterator it = b1.ListByName();
    assert(!it.AtEnd() && it.Name() == "Jane Hacker" && it.Addr() == "Main Street 17" && it.Account() == "Xuj5#94");
    it.Next();
    assert(!it.AtEnd() && it.Name() == "John Smith" && it.Addr() == "Main Street 17" && it.Account() == "Z343rwZ");
    it.Next();
    assert(!it.AtEnd() && it.Name() == "John Smith" && it.Addr() == "Oak Road 23" && it.Account() == "123/456/789");
    it.Next();
    assert(!it.AtEnd() && it.Name() == "Peter Hacker" && it.Addr() == "Main Street 17" && it.Account() == "634oddT");
    it.Next();
    assert(it.AtEnd());

    assert(b1.Death("John Smith", "Main Street 17"));
    CTaxRegister b2;
    assert(b2.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert(b2.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert(!b2.Income("634oddT", 4000));
    assert(!b2.Expense("John Smith", "Main Street 18", 500));
    assert(!b2.Audit("John Nowak", "Second Street 23", acct, sumIncome, sumExpense));
    assert(!b2.Death("Peter Nowak", "5-th Avenue"));
    assert(!b2.Birth("Jane Hacker", "Main Street 17", "4et689A"));
    assert(!b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert(b2.Death("Jane Hacker", "Main Street 17"));
    assert(b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert(b2.Audit("Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense));
    assert(acct == "Xuj5#94");
    assert(sumIncome == 0);
    assert(sumExpense == 0);
    assert(!b2.Birth("Joe Hacker", "Elm Street 23", "AAj5#94"));

    return 0;
}