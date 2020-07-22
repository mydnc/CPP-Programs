#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;

class CTimeStamp
{
public:
  int m_Year, m_Month, m_Day, m_Hour, m_Minute, m_Sec;
  CTimeStamp()
  {
    m_Year = 0;
    m_Month = 0;
    m_Day = 0;
    m_Hour = 0;
    m_Minute = 0;
    m_Sec = 0;
  }
  CTimeStamp(int year, int month, int day, int hour, int minute, int sec)
  {
    m_Year = year;
    m_Month = month;
    m_Day = day;
    m_Hour = hour;
    m_Minute = minute;
    m_Sec = sec;
  }
  int Compare(const CTimeStamp &x) const
  {
    if (this->m_Year == x.m_Year)
    {
      if (this->m_Month == x.m_Month)
      {
        if (this->m_Day == x.m_Day)
        {
          if (this->m_Hour == x.m_Hour)
          {
            if (this->m_Minute == x.m_Minute)
            {
              if (this->m_Sec == x.m_Sec)
              {
                return 0;
              }
              else if (this->m_Sec > x.m_Sec)
              {
                return 1;
              }
              else
              {
                return -1;
              }
            }
            else if (this->m_Minute > x.m_Minute)
            {
              return 1;
            }
            else
            {
              return -1;
            }
          }
          else if (this->m_Hour > x.m_Hour)
          {
            return 1;
          }
          else
          {
            return -1;
          }
        }
        else if (this->m_Day > x.m_Day)
        {
          return 1;
        }
        else
        {
          return -1;
        }
      }
      else if (this->m_Month > x.m_Month)
      {
        return 1;
      }
      else
      {
        return -1;
      }
    }
    else if (this->m_Year > x.m_Year)
    {
      return 1;
    }
    else
    {
      return -1;
    }
  }
  friend ostream &operator<<(ostream &os, const CTimeStamp &x)
  {
    os << x.m_Year << "-";
    if (x.m_Month < 10)
      os << 0;

    os << x.m_Month;
    if (x.m_Day < 10)
      os << 0;

    os << "-" << x.m_Day << " ";
    if (x.m_Hour < 10)
      os << 0;

    os << x.m_Hour << ":";
    if (x.m_Minute < 10)
      os << 0;

    os << x.m_Minute << ":";
    if (x.m_Sec < 10)
      os << 0;

    os << x.m_Sec << " ";
    return os;
  }
  void printTime() const
  {
    cout << m_Year << "-" << m_Month << "-" << m_Day << " " << m_Hour << ":" << m_Minute << ":" << m_Sec << " ";
  }
};
//=================================================================================================
class CMailBody
{
private:
  int m_Size;
  const char *m_Data;

public:
  CMailBody()
  {
    m_Size = 0;
    m_Data = NULL;
  }
  CMailBody(int size, const char *data)
  {
    m_Size = size;
    m_Data = data;
  }
  // copy cons/op=/destructor is correctly implemented in the testing environment
  friend ostream &operator<<(ostream &os, const CMailBody &x)
  {
    return os << "mail body: " << x.m_Size << " B";
  }
  void printMailBody()
  {
    cout << "BodySize: " << m_Size << " B"
         << " Body: " << m_Data << " ";
  }
};
//=================================================================================================
class CAttach
{
public:
  CAttach(int x) : m_X(x), m_RefCnt(1)
  {
  }
  void AddRef(void) const
  {
    m_RefCnt++;
  }
  void Release(void) const
  {
    if (!--m_RefCnt)
      delete this;
  }
  void printAttach(void) const
  {
    //cout << " Size: " << m_X << " ";
  }

private:
  int m_X;
  mutable int m_RefCnt;
  CAttach(const CAttach &x);
  CAttach &operator=(const CAttach &x);
  ~CAttach(void) = default;
  friend ostream &operator<<(ostream &os, const CAttach &x)
  {
    return os << "attachment: " << x.m_X << " B";
  }
};

class CMail
{
public:
  CTimeStamp m_TimeStamp;
  string m_From;
  CMailBody m_Body;
  const CAttach *m_Attach;
  CMail(const CTimeStamp &timeStamp, const string &from, const CMailBody &body, const CAttach *attach)
  {
    m_TimeStamp = timeStamp;
    m_From = from;
    m_Body = body;
    m_Attach = attach;
    if (m_Attach != NULL)
    {
      m_Attach->AddRef();
    }
  }
  const string &From(void) const
  {
    return m_From;
  }
  const CMailBody &Body(void) const
  {
    return m_Body;
  }
  const CTimeStamp &TimeStamp(void) const
  {
    return m_TimeStamp;
  }
  const CAttach *Attachment(void) const
  {
    return m_Attach;
  }

  friend ostream &operator<<(ostream &os, const CMail &x)
  {
    os << x.TimeStamp();
    os << x.From() << " ";
    os << x.Body();
    if (x.Attachment() != NULL)
      os << " + " << *x.m_Attach;

    //os << endl;
    return os;
  }
  void printMail()
  {
    m_TimeStamp.printTime();
    cout << m_From << " ";
    m_Body.printMailBody();
    m_Attach->printAttach();
  }

private:
  // todo
};

struct TimeCompare
{
  bool operator()(const CTimeStamp &ins1, const CTimeStamp &ins2) const
  {
    if (ins1.Compare(ins2) < 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

class CMailBox
{
public:
  map<string, multimap<CTimeStamp, CMail, TimeCompare>> m_Map;

  CMailBox()
  {
  }

  bool Delivery(const CMail &mail)
  {
    m_Map["inbox"].insert(make_pair(mail.m_TimeStamp, mail));
    return true;
  }

  bool NewFolder(const string &folderName)
  {
    auto it = m_Map.find(folderName);

    if (it != m_Map.end())
    {
      return false;
    }

    multimap<CTimeStamp, CMail, TimeCompare> empty;
    m_Map.insert(make_pair(folderName, empty));
    return true;
  }

  bool MoveMail(const string &fromFolder, const string &toFolder)
  {

    auto src = m_Map.find(fromFolder);
    auto dest = m_Map.find(toFolder);

    //merge works only after C++ version 17 (use the flag -std=c++17)
    dest->second.merge(src->second);
    
    return true;
  }

  void printMailBox()
  {
    map<string, multimap<CTimeStamp, CMail, TimeCompare>>::iterator it;
    for (it = m_Map.begin(); it != m_Map.end(); it++)
    {

      for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
      {
        cout << it->first << endl;
        it2->second.printMail();
      }
    }
    cout << endl;
  }

  list<CMail> ListMail(const string &folderName, const CTimeStamp &from, const CTimeStamp &to) const
  {
    list<CMail> myList;
    auto it = m_Map.find(folderName);

    if (it == m_Map.end())
    {
      return myList;
    }

    auto low = it->second.lower_bound(from);
    auto upper = it->second.upper_bound(to);

    while (true)
    {
      if (low == upper)
        break;

      myList.push_back(low->second);
      low++;
    }

    return myList;
  }

  set<string> ListAddr(const CTimeStamp &from, const CTimeStamp &to) const
  {
    set<string> mySet;

    for (auto it = m_Map.begin(); it != m_Map.end(); it++)
    {
      auto low = it->second.lower_bound(from);
      auto upper = it->second.upper_bound(to);
      while (true)
      {
        if (low == upper)
          break;

        mySet.insert(low->second.m_From);
        low++;
      }
    }
    return mySet;
  }

private:
  // todo
};

static string showMail(const list<CMail> &l)
{
  ostringstream oss;
  for (const auto &x : l)
    oss << x << endl;

  return oss.str();
}

static string showUsers(const set<string> &s)
{
  ostringstream oss;
  for (const auto &x : s)
    oss << x << endl;

  return oss.str();
}

int main()
{
  //list<CMail> mailList;
  //set<string> users;
  CAttach *att;
  CMailBox m0;
  assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
  assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"), nullptr)));
  att = new CAttach(200);
  assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), att)));
  assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));

  att->Release();
  att = new CAttach(97);
  assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"), att)));
  att->Release();

  assert(showMail(m0.ListMail("inbox",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n"
                                                                        "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                        "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n"
                                                                        "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n");

  assert(showMail(m0.ListMail("inbox",
                              CTimeStamp(2014, 3, 31, 15, 26, 23),
                              CTimeStamp(2014, 3, 31, 16, 12, 48))) == "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n");
  assert(showUsers(m0.ListAddr(CTimeStamp(2000, 1, 1, 0, 0, 0),
                               CTimeStamp(2050, 12, 31, 23, 59, 59))) == "boss1@fit.cvut.cz\n"
                                                                         "user1@fit.cvut.cz\n"
                                                                         "user2@fit.cvut.cz\n");
  assert(showUsers(m0.ListAddr(CTimeStamp(2014, 3, 31, 15, 26, 23),
                               CTimeStamp(2014, 3, 31, 16, 12, 48))) == "boss1@fit.cvut.cz\n"
                                                                        "user2@fit.cvut.cz\n");

  CMailBox m1;
  assert(m1.NewFolder("work"));
  assert(m1.NewFolder("spam"));
  assert(!m1.NewFolder("spam"));
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
  att = new CAttach(500);
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"), att)));
  att->Release();
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), nullptr)));
  att = new CAttach(468);
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));
  att->Release();
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"), nullptr)));
  assert(showMail(m1.ListMail("inbox",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                        "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                        "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
  assert(showMail(m1.ListMail("work",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
  assert(m1.MoveMail("inbox", "work"));
  assert(showMail(m1.ListMail("inbox",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
  assert(showMail(m1.ListMail("work",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                        "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                        "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 19, 24, 13), "user2@fit.cvut.cz", CMailBody(14, "mail content 4"), nullptr)));
  att = new CAttach(234);
  assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 13, 26, 23), "user3@fit.cvut.cz", CMailBody(9, "complains"), att)));
  att->Release();
  assert(showMail(m1.ListMail("inbox",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                        "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");
  assert(showMail(m1.ListMail("work",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                        "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                        "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
  assert(m1.MoveMail("inbox", "work"));
  assert(showMail(m1.ListMail("inbox",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");



  assert(showMail(m1.ListMail("work",
                              CTimeStamp(2000, 1, 1, 0, 0, 0),
                              CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                        "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                        "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                        "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                        "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n"
                                                                        "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");

  return 0;
}