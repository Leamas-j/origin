#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Observer {
public:
  virtual void onWarning(const string&) {};
  virtual void onError(const string&) {};
  virtual void onFatalError(const string&) {};
};

class ErrorsManage
{
private:
  vector<Observer*> __observers;

public:
  void add_observer(Observer* obs)
  {
    __observers.push_back(obs);
  }

  void remove_observer(Observer* obs)
  {
    auto it = remove(__observers.begin(), __observers.end(), obs);
    __observers.erase(it, __observers.end());
  }

  void warning(const string& message) const
  {
    for (auto obs : __observers)
    {
      obs->onWarning(message);
    }
  }
  void error(const string& message) const
  {
    for (auto obs : __observers)
    {
      obs->onError(message);
    }
  }
  void fatalError(const string& message) const
  {
    for (auto obs : __observers)
    {
      obs->onFatalError(message);
    }
  }
};

class Warning : public Observer
{
public:
  void onWarning(const string& message) override
  {
    cout << "Warning: " << message << endl;
  }
};

class Error : public Observer
{
private:
  ofstream fout{ "LogError.txt" };

public:
  void onError(const string& message) override
  {
    fout << "Error: " << message << endl;
  }

  ~Error() {
    fout.close();
  }
};

class FatalError : public Observer
{
private:
  ofstream fout{ "LogFatalError.txt" };

public:
  void onFatalError(const string& message) override
  {
    fout << "Fatal error: " << message << endl;
    cout << "Fatal error: " << message << endl;
  }

  ~FatalError() {
    fout.close();
  }
};


int main()
{
  ErrorsManage errMan;
  Warning warn;
  Error err;
  FatalError ferr;

  errMan.add_observer(&warn);
  errMan.add_observer(&err);
  errMan.add_observer(&ferr);

  errMan.warning("This is a warning!\n");
  errMan.error("This is a error!\n");
  errMan.fatalError("This is a fatal error!\n");

  return 0;
}
