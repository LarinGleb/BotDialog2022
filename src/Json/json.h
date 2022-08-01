#ifndef __JSON_H__
#define __JSON_H__

#include <iostream>

std::string GetJsonString(const std::string path);
std::string GetProperty(const std::string property, const std::string path);
bool IsAdmin(const int id, const std::string path);
void AddAdmin(const int id, const std::string path);
#endif