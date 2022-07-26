#ifndef __JSON_H__
#define __JSON_H__

#include <iostream>

std::string GetJsonString(std::string path);
std::string GetProperty(std::string property, std::string path);
bool IsAdmin(int id, std::string path);
void AddAdmin(int id, std::string path);
#endif