#include "parameterset.h"

ParameterSet::ParameterSet()
{

}

ParameterSet::~ParameterSet()
{

}


bool ParameterSet::getValue(const string &_name, bool &_value) const
{
    auto itr = type_dict.find(_name);
    auto vitr = bool_dict.find(_name);
    if(itr == type_dict.end() || itr -> second != BOOL|| vitr == bool_dict.end())
        return false;
    _value = vitr -> second;
    return true;
}

void ParameterSet::setValue(const string &_name, const bool &_value)
{
    auto itr = type_dict.find(_name);
    if( itr == type_dict.end() || type_dict[_name] != BOOL)
        return ;
    bool_dict.erase(bool_dict.find(_name));
    bool_dict.insert(std::make_pair(_name, _value));
}

bool ParameterSet::getValue(const string &_name, int &_value) const
{
    auto itr = type_dict.find(_name);
    auto vitr = int_dict.find(_name);
    if(itr == type_dict.end() || itr -> second != INT || vitr == int_dict.end())
        return false;
    _value = vitr -> second;
    return true;
}

void ParameterSet::setValue(const string &_name, const int &_value)
{
    auto itr = type_dict.find(_name);
    if( itr == type_dict.end() || type_dict[_name] != INT)
        return ;
    int_dict.erase(int_dict.find(_name));
    int_dict.insert(std::make_pair(_name, _value));
}

bool ParameterSet::getValue(const string &_name, double &_value) const
{
    auto itr = type_dict.find(_name);
    auto vitr = double_dict.find(_name);
    if(itr == type_dict.end() || itr -> second != DOUBLE || vitr == double_dict.end())
        return false;
    _value = vitr -> second;
    return true;
}

void ParameterSet::setValue(const string &_name, const double &_value)
{
    auto itr = type_dict.find(_name);
    if( itr == type_dict.end() || type_dict[_name] != DOUBLE)
        return ;
    double_dict.erase(double_dict.find(_name));
    double_dict.insert(std::make_pair(_name, _value));
}


void ParameterSet::addParameter(const string &_name, bool _defaultValue)
{
    type_dict.insert(std::make_pair(_name, BOOL));
    bool_dict.insert(std::make_pair(_name, _defaultValue));
}

void ParameterSet::addParameter(const string &_name, int _defaultValue)
{
    type_dict.insert(std::make_pair(_name, INT));
    int_dict.insert(std::make_pair(_name, _defaultValue));
}

void ParameterSet::addParameter(const string &_name, double _defaultValue)
{
    type_dict.insert(std::make_pair(_name, DOUBLE));
    double_dict.insert(std::make_pair(_name, _defaultValue));
}



