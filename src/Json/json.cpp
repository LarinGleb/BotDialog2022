#include <iostream>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filewritestream.h>

#include "json.h"


std::string GetJsonString(const std::string path) {
    std::ifstream settings(path);
    std::string json;
    std::string line;
    if (settings.is_open()) {
        while (std::getline(settings, line)) { json += line;}   
        settings.close();
    }
    return json;

}

std::string GetProperty(const std::string property, const std::string path) {
   
    rapidjson::Document settings;
    settings.Parse(GetJsonString(path).c_str());
    rapidjson::Value& propertyValue = settings[property.c_str()];
    return propertyValue.GetString();

}

bool IsAdmin(const int id, const std::string path) {
    rapidjson::Document admins;
    admins.Parse(GetJsonString(path).c_str());
    rapidjson::Value& adminsList = admins["admin"].GetArray();
    
    for (rapidjson::SizeType i = 0; i < adminsList.Size(); i++)
    {
        rapidjson::Value& idAdmin = adminsList[rapidjson::SizeType(i)];
        if(idAdmin.GetInt() == id) {
            return true;
        }
    }
    return false;
}
void AddAdmin(const int id, const std::string path) {
    rapidjson::Document settings;
    settings.Parse(GetJsonString(path).c_str());
    settings["admin"].PushBack(id, settings.GetAllocator());
    FILE* fp = fopen(path.c_str(), "wb");
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    settings.Accept(writer);
    fclose(fp);
}

