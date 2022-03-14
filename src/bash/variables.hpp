#pragma once

#include <string>
#include <unordered_map>

namespace bash {

/*
 * Переменные окружения.
 *
 * Введя в bash команду VAR=VALUE без кавычек, мы присваиваем переменное
 * VAR значение VALUE
 */
struct Variables : public std::unordered_map<std::string, std::string> {
  std::string serialize() const;
};

}  // namespace bash
