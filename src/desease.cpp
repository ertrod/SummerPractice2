#include "practice.h"

namespace practice
{
    // реализация классов связанных с болезнями
    DeseaseName::DeseaseName() {}
    DeseaseName::DeseaseName(std::string n)
    {
        _name = new std::string(n);
    }
    DeseaseName::~DeseaseName()
    {
        delete _name;
    }

    std::string* DeseaseName::name() const { return _name; }
    void DeseaseName::set_name(std::string n) 
    { 
        delete _name;
        _name = new std::string(n); 
    }

    std::string DeseaseName::to_string() 
    {
        return *_name;
    }

    bool operator== (const DeseaseName& x, const DeseaseName& y)
    {
        return *(x.name()) == *(y.name());
    }

    bool operator!= (const DeseaseName& x, const DeseaseName& y)
    {
        return !(x == y);
    }

    Threatment::Threatment() : MedicineDBEntry() {}
    Threatment::Threatment(TObj<MedicineName>* m, int a) : MedicineDBEntry(m, a) {}

    bool operator== (const Threatment& x, const Threatment& y)
    {
        return (x.name()->obj->to_string() == y.name()->obj->to_string()) &&
            (x.amount() == y.amount());
    }

    bool operator!= (const Threatment& x, const Threatment& y)
    {
        return !(x == y);
    }


    DeseaseDBEntry::DeseaseDBEntry(TObj<DeseaseName>* n, TObj<DeseaseName>* s,
        TObj<DeseaseName>* p, TObj<Threatment>* t)
        : name(n), symptome(s), procedure(p), threatment(t),
        nameid(n->id), symptomeid(s->id), procedureid(p->id), threatmentid(t->id)
    { }

    std::string DeseaseDBEntry::to_string()
    {
        return name->obj->to_string() + ", " + symptome->obj->to_string() + ", " +
            procedure->obj->to_string() + ", " + threatment->obj->to_string(); 
    }

    void DeseaseDBEntry::checkid()
    {
        nameid = name->id;
        symptomeid = symptome->id;
        procedureid = procedure->id;
        threatmentid = threatment->id;
    }

    bool operator== (DeseaseDBEntry& x, DeseaseDBEntry& y)
    {
        return (*(x.name->obj) == *(y.name->obj)) && (*(x.symptome->obj) == *(y.symptome->obj)) &&
            (*(x.procedure->obj) == *(y.procedure->obj)) && (*(x.threatment->obj) == *(y.threatment->obj));
    }

    bool operator!= (DeseaseDBEntry& x, DeseaseDBEntry& y)
    {
        return !(x == y);
    }
}   