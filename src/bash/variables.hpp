#pragma once

#include <string>
#include <unordered_map>

namespace bash {

/*
 * Переменные окружения.
 *
 * Введя в bash команду VAR=VALUE, мы присваиваем переменное VAR значение VALUE
 */
using Variables = std::unordered_map<std::string, std::string>;

}  // namespace bash
