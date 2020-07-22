#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <list>

using namespace std;
typedef list<string> Stack;

string seq;
string cmd;
long long int arg = 0;

long long int convert_to_decimal(char key)
{
    static map<char, long long int> table = {{'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}};
    return table[key];
}

long long int roman_to_number(const string &roman)
{
    static map<string, long long int> romans;

    auto it = romans.find(roman);
    if (it != romans.end())
    {
        return it->second;
    }

    long long int ret = 0;
    for (size_t i = 0; i < roman.size(); ++i)
    {
        long long int v1 = convert_to_decimal(roman[i]);

        if (i + 1 < roman.size())
        {
            long long int v2 = convert_to_decimal(roman[i + 1]);

            if (v1 >= v2)
            {
                ret = ret + v1;
            }
            else
            {
                ret = ret + v2 - v1;
                ++i;
            }
        }
        else
        {
            ret = ret + v1;

            ++i;
        }
    }

    romans[roman] = ret;
    return ret;
}

void print_list(const list<string> &romans)
{
    cout << "> ";
    cout << arg;
    cout << " = ";

    list<string>::const_iterator it = romans.begin();
    while (it != romans.end())
    {
        cout << *it;

        ++it;
        if (it != romans.end())
        {
            cout << "+";
        }
    }

    cout << endl;
}

bool check_validity(const string &roman)
{
    static map<string, bool> cache;
    auto pair = cache.find(roman);
    if (cache.end() != pair)
    {
        return pair->second;
    }

    regex regular_expression("M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})");
    bool ret = regex_match(roman, regular_expression);
    cache[roman] = ret;
    return cache[roman];
}

long long int solve_puzzle(list<string> &stack, long long int num, const string &roman, bool ignore_print = false)
{
    if (roman.empty() && num == arg)
    {
        if (!ignore_print)
        {
            print_list(stack);
        }

        return 1;
    }

    long long count = 0;
    long long int decimal = 0;
    for (size_t length = 1; length <= roman.size(); ++length)
    {
        string roman_item = roman.substr(0, length);
        if (!check_validity(roman_item))
        {
            break;
        }

        if ((decimal = roman_to_number(roman.substr(0, length))) == 0)
        {
            break;
        }

        string new_item = roman.substr(length, roman.size() - length);
        if (!ignore_print)
        {
            stack.push_back(roman_item);
        }

        count += solve_puzzle(stack, num + decimal, new_item, ignore_print);

        if (!ignore_print)
        {
            stack.pop_back();
        }
    }

    return count;
}

int main()
{
    cout << "Sequence:" << endl;

    char ch = 0;
    for (;;)
    {
        cin.get(ch);

        if (ch == '\n')
        {
            break;
        }

        seq.push_back(ch);
    }

    if (seq.empty() || (ch == 0 && cin.eof()))
    {
        cout << "Invalid input." << endl;
        return -1;
    }

    list<char> valid_romans = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    for (string::const_iterator character = seq.begin();
         character != seq.end();
         ++character)
    {
        if (find(valid_romans.begin(), valid_romans.end(), *character) == valid_romans.end())
        {
            cout << "Invalid input." << endl;
            return -1;
        }
    }

    cout << "Operations:" << endl;

    for (;;)
    {
        cmd.clear();
        string num;
        int space = 0;
        while (1)
        {
            if (cin.eof())
            {
                return 0;
            }

            char ch = 0;
            cin.get(ch);

            if (isdigit(ch))
            {
                if (cmd.empty())
                {
                    cout << "Invalid input." << endl;
                    return -1;
                }
                else
                {
                    num.push_back(ch);
                }
            }
            else if (ch == ' ')
            {
                space = true;

                if (!num.empty())
                {
                    cout << "Invalid input." << endl;
                    return -1;
                }
            }
            else if (ch != '\n')
            {
                if (!space)
                {
                    cmd.push_back(ch);
                }
                else
                {
                    cout << "Invalid input." << endl;
                    return -1;
                }
            }
            else
            {
                break;
            }
        }

        if (!cmd.empty() && num.empty())
        {
            cout << "Invalid input." << endl;
            return -1;
        }
        else if (cmd.empty())
        {
            cout << "Invalid input." << endl;
            break;
        }

        arg = atoll(num.c_str());
        if (arg <= 0 || to_string(arg) != num)
        {
            cout << "Invalid input." << endl;
            return -1;
        }

        Stack stack;
        if (cmd == "count")
        {
            cout << arg << ": " << solve_puzzle(stack, 0, seq, true) << endl;
        }
        else if (cmd == "list")
        {
            long long int count = solve_puzzle(stack, 0, seq);
            cout << arg << ": " << count << endl;
        }
        else
        {
            cout << "Invalid input." << endl;
            return -1;
        }
    }

    return 0;
}