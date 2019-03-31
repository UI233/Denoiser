#ifndef PARAMETERSET_H
#define PARAMETERSET_H

#include <string>
#include <map>
#include <string>
using std::string;
using std::map;
enum Type{
    BOOL,
    DOUBLE,
    INT
};

class ParameterSet
{
public:
    ParameterSet();
    ~ParameterSet();

public:
    string getName() const {return name_;}
    void setName(const string &_name) {name_ = _name;}
    string getLabel() const {return label_;}
    void setLabel(const string &_label) {label_ = _label;}
    string getIntroduction() const {return introduction_;}
    void setIntroduction(const string &_introduction) {introduction_ = _introduction;}

    bool getValue(const string &_name, bool &_value) const;
    void setValue(const string &_name, const bool &_value);
    bool getValue(const string &_name, int &_value) const;
    void setValue(const string &_name, const int &_value);
    bool getValue(const string &_name, double &_value) const;
    void setValue(const string &_name, const double &_value);

    bool getStringListIndex(const string &_name, int &_index) const;
    void setStringListIndex(const string &_name, const int &_index);

    void addParameter(const string &_name, bool _defaultValue);
    void addParameter(const string &_name, int _defaultValue);
    void addParameter(const string &_name, double _defaultValue);

    void removeAllParameter(){
        type_dict.clear();
        int_dict.clear();
        double_dict.clear();
        bool_dict.clear();
    }

private:
    string name_;
    string label_;
    string introduction_;
    map<string, Type> type_dict;
    map<string, int> int_dict;
    map<string, double> double_dict;
    map<string, bool> bool_dict;
};

#endif // PARAMETERSET_H
