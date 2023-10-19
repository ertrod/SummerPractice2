#include "practice.h"

namespace practice
{
    // реализация классов связанных с лекарствами
    MedicineName::MedicineName() : DeseaseName() {}
    MedicineName::MedicineName(std::string n) : DeseaseName(n) {}

    MedicineDBEntry::MedicineDBEntry() : _name(0), _amount(0), _nameid(0) {}
    MedicineDBEntry::MedicineDBEntry(TObj<MedicineName>* n, int a) 
        : _name(n), _amount(a), _nameid(n->id)
    {}

    TObj<MedicineName>* MedicineDBEntry::name() const { return _name; }
    int MedicineDBEntry::amount() const { return _amount; }
    int MedicineDBEntry::id() const { return _nameid; }

    void MedicineDBEntry::set_name(TObj<MedicineName>* n) { _name = n; }
    void MedicineDBEntry::set_id(int id) { _nameid = id; }
    void MedicineDBEntry::set_amount(int a) { _amount = a; }

    void MedicineDBEntry::add_amount(int a) 
    { 
        if (a >= _amount)
            _amount = 0;
        else
            _amount -= a;
    }

    std::string MedicineDBEntry::to_string()
    {
        if (_name) 
            return *(_name->obj->name()) + ", " + std::to_string(_amount);
        else
            return "MedicineDBEntry isn't set";
    }
    void MedicineDBEntry::checkid()
    {
        _nameid = _name->id;
    }
 
    bool operator== (const MedicineDBEntry& x, const MedicineDBEntry& y)
    {
        return x.name() == y.name();
    }

    bool operator!= (const MedicineDBEntry& x, const MedicineDBEntry& y)
    {
        return !(x == y);
    }

    MedicineAnalog::MedicineAnalog(TObj<MedicineName>* n, TObj<MedicineName>* a)
        : _name(n), _analog(a), nameid(n->id), analogid(a->id)
    {}

    TObj<MedicineName>* MedicineAnalog::name() const { return _name; }
    TObj<MedicineName>* MedicineAnalog::analog() const { return _analog; }

    void MedicineAnalog::checkid()
    {
        nameid = _name->id;
        analogid = _analog->id;
    }

    bool operator== (MedicineAnalog& x, MedicineAnalog& y)
    {
        return (*(x._name->obj) == *(y._name->obj)) && (*(x._analog->obj) == *(y._analog->obj));
    }

    bool operator!= (MedicineAnalog& x, MedicineAnalog& y)
    {
        return !(x == y);
    }

    std::string MedicineAnalog::to_string()
    {
        return _name->obj->to_string() + ", " + _analog->obj->to_string();
    }

    
}