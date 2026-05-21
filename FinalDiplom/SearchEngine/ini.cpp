#include "ini.h"

#include <vector>

Ini::Ini(const std::string& fileNameIni)
{
  fin_.open(fileNameIni);
  if (!fin_.is_open()) {
    throw std::runtime_error("Не удалось открыть файл " + fileNameIni + "!");
  }

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(fin_, line))
  {
    lines.push_back(line);
  }

  if (lines.size() < 7) {
    throw std::runtime_error("Недостаточно параметров в файле конфигурации!");
  }

  bd_host_ = lines[0];
  bd_port_ = lines[1];
  bd_name_ = lines[2];
  bd_user_name_ = lines[3];
  bd_user_password_ = lines[4];
  startDir_ = lines[5];
  extensions_ = lines[6];

  if (bd_host_.empty()) throw std::runtime_error("Адрес базы данных не может быть пустым!");
  if (bd_port_.empty()) throw std::runtime_error("Порт базы данных не может быть пустым!");
  if (bd_name_.empty()) throw std::runtime_error("Имя базы данных не может быть пустым!");
  if (bd_user_name_.empty()) throw std::runtime_error("Имя пользователя базы данных не может быть пустым!");
  if (bd_user_password_.empty()) throw std::runtime_error("Пароль базы данных не может быть пустым!");
  if (startDir_.empty()) throw std::runtime_error("Стартовая директория не может быть пустой!");
  if (extensions_.empty()) throw std::runtime_error("Список разрешенных расширений не может быть пустой!");
}

std::string Ini::get_startDir()
{
  return startDir_;
}

std::string Ini::get_bd_host()
{
  return bd_host_;
}

std::string Ini::get_bd_port()
{
  return bd_port_;
}

std::string Ini::get_bd_name()
{
  return bd_name_;
}

std::string Ini::get_bd_user_name()
{
  return bd_user_name_;
}

std::string Ini::get_bd_user_password()
{
  return bd_user_password_;
}

std::string Ini::get_extensions()
{
  return extensions_;
}

Ini :: ~Ini()
{
  fin_.close();
}
