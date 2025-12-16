#include <iostream>
#include <fstream>

using namespace std;

class LogCommand {
public:
  virtual ~LogCommand() = default;
  virtual void print(const string& message) = 0;
};

class LogConsole : public LogCommand
{
  void print(const string& message) override
  {
    cout << message << endl;
  }
};

class LogFile : public LogCommand
{
private:
  ofstream fout{ "LogError.txt" };
public:
  void print(const string& message) override
  {
    fout << message << endl;
  }

  ~LogFile()
  {
    fout.close();
  }
};

void print(LogCommand& lComm, const string& message)
{
  lComm.print(message);
}

int main()
{
  LogFile lf;
  LogConsole lc;

  print(lc, "Log to console");
  print(lf, "Log to file");

  return 0;
}
