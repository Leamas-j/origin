#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

enum Type {
  WARNING,
  ERROR,
  FATAL_ERROR,
  UNKNOWN_MESSAGE
};

class LogMessage
{
private:
  Type __type;
  string __message;

public:
  LogMessage(Type type, string const& message) : __type(type), __message(message) {}

  Type type() const
  {
    return __type;
  }
  const string& message() const
  {
    return __message;
  }
};

class Handler
{
public:
  virtual void handle(const LogMessage& msg) = 0;
  virtual void set_next_handler(Handler* handler) = 0;
};

class WarningsHandle : public Handler
{
private:
  Handler* next_handler = nullptr;

public:
  void set_next_handler(Handler* handler) override
  {
    next_handler = handler;
  }

  void handle(const LogMessage& msg) override
  {
    if (msg.type() == Type::WARNING)
    {
      cout << msg.message();
    }
    else if (next_handler != nullptr)
    {
      next_handler->handle(msg);
    }
  }
};

class ErrorHandle : public Handler
{
private:
  Handler* next_handler = nullptr;
  ofstream fout{ "LogError.txt" };

public:
  void set_next_handler(Handler* handler) override
  {
    next_handler = handler;
  }

  void handle(const LogMessage& msg) override
  {
    if (msg.type() == Type::ERROR)
    {
      fout << msg.message() << endl;
    }
    else if (next_handler != nullptr)
    {
      next_handler->handle(msg);
    }
  }

  ~ErrorHandle()
  {
    fout.close();
  }
};

class FatalErrorHandle : public Handler
{
private:
  Handler* next_handler = nullptr;

public:
  void set_next_handler(Handler* handler) override
  {
    next_handler = handler;
  }

  void handle(const LogMessage& msg) override
  {
    if (msg.type() == Type::FATAL_ERROR)
    {
      throw runtime_error(msg.message());
    }
    else if (next_handler != nullptr)
    {
      next_handler->handle(msg);
    }
  }
};

class UnknownErrorHandle : public Handler
{
private:
  Handler* next_handler = nullptr;

public:
  void set_next_handler(Handler* handler) override
  {
    next_handler = handler;
  }

  void handle(const LogMessage& msg) override
  {
    if (msg.type() == Type::UNKNOWN_MESSAGE)
    {
      throw runtime_error(msg.message());
    }
    else
    {
      throw runtime_error("Unknown error type!");
    }
  }
};

int main()
{
  Handler* fatal_err = new FatalErrorHandle();
  Handler* err = new ErrorHandle();
  Handler* warn = new WarningsHandle();
  Handler* unknown_err = new UnknownErrorHandle();

  fatal_err->set_next_handler(err);
  err->set_next_handler(warn);
  warn->set_next_handler(unknown_err);

  LogMessage mess(Type::ERROR, "Usual error is written to the file!\n");
  fatal_err->handle(mess);

  LogMessage mess_1(Type::WARNING, "Warning is displayed in the console!\n");
  fatal_err->handle(mess_1);

  LogMessage mess_3(Type::UNKNOWN_MESSAGE, "Unknown message is threw an exception!");
  try {
    fatal_err->handle(mess_3);
  }
  catch (const exception& m) {
    cout << m.what() << endl;
  }

  LogMessage mess_2(Type::FATAL_ERROR, "Fatal Error is threw an exception!");
  try {
    fatal_err->handle(mess_2);
  }
  catch (const exception& m) {
    cout << m.what() << endl;
    return 0;
  }

  return 0;
}
