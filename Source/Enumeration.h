/*
  ==============================================================================

    Enumeration.h
    Created: 27 Mar 2024 10:38:13pm
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <map>
#include <string>
#include <memory>

template <class TEnum>
class Enumeration //: public std::enable_shared_from_this<TEnum>
{
public:
    int id;
    std::string name;

    static TEnum* getByID(const int& id)
    {
        TEnum* ptr = nullptr;
        try {
            ptr = enum_map[id];
        }
        catch (const std::exception& ex)
        {
            system("PAUSE"); // haha
        }
        return ptr;
    }

    static std::shared_ptr<std::unordered_map<int, TEnum*>> getAll()
    {
        return std::make_shared< std::unordered_map<int, TEnum*>>(enum_map);
    }
protected:
    Enumeration(const int& id, const std::string& name)
        : id{ id }, name{ name }
    {
        enum_map.insert_or_assign(this->id, reinterpret_cast<TEnum*>(this));
    }

    static inline std::unordered_map<int, TEnum*> enum_map{};
};