#include "practice.h"

namespace practice
{
    // реализация класса базы общей базы данных
    DeseaseDB::DeseaseDB()
    {
        names = new Table<DeseaseName>();
        symptomes = new Table<DeseaseName>();
        procedures = new Table<DeseaseName>();
        threatment = new Table<Threatment>();

        desease_table = new Table<DeseaseDBEntry>();

        medicines = new Table<MedicineName>();
        stock = new Table<MedicineDBEntry>();

        analogs = new Table<MedicineAnalog>();
    }

    DeseaseDB::~DeseaseDB()
    {
        //dump();
        delete names;
        delete symptomes;
        delete procedures;
        delete threatment;
        delete desease_table;
        delete medicines;
        delete stock;
        delete analogs;
    }

    // =============================
    // getters
    // =============================

    Table<DeseaseName>* DeseaseDB::names_table() { return names; }
    Table<DeseaseName>* DeseaseDB::symptomes_table() { return symptomes; }
    Table<DeseaseName>* DeseaseDB::procedures_table() { return procedures; }
    Table<Threatment>* DeseaseDB::threatment_table() { return threatment; }

    Table<DeseaseDBEntry>* DeseaseDB::deseasedb_table() { return desease_table; }
    
    Table<MedicineName>* DeseaseDB::medicines_table() { return medicines; }
    Table<MedicineDBEntry>* DeseaseDB::stock_table() { return stock; }
    
    Table<MedicineAnalog>* DeseaseDB::analogs_table() { return analogs; }

    // =============================
    // names table
    // =============================

    int DeseaseDB::add_name(std::string n)
    {
        return names->add_node(new DeseaseName(n));
    }

    int DeseaseDB::remove_name(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = names->remove(t);
        delete t;

        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_procedure(n);
            if (v)
                remove_desease(v->front()->obj);
            delete v;

            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_name(int id)
    {
        TObj<DeseaseName>* res = names->at_pos(id);
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_name(res->obj->to_string());
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);

            delete v;
            names->remove_at(id);
            return 1;
        }
        return 0;
    }

    int DeseaseDB::change_name(TObj<DeseaseName>* o, std::string n)
    {
        if (!n.empty())
            if (!find_name(n))
            {
                o->obj->set_name(n);
                return o->id;
            }
        return -1;
    }

    TObj<DeseaseName>* DeseaseDB::find_name(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = names->find(t);
        delete t;
        return res;
    }

    // =============================
    // symptomes table
    // =============================

    int DeseaseDB::add_symptome(std::string n)
    {
        return symptomes->add_node(new DeseaseName(n));
    }

    int DeseaseDB::remove_symptome(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = symptomes->remove(t);
        delete t;

        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_procedure(n);
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;

            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }
    
    int DeseaseDB::remove_symptome(int id)
    {
        TObj<DeseaseName>* res = symptomes->at_pos(id);
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_symptome(res->obj->to_string());
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;
            symptomes->remove_at(id);
            return 1;
        }
        return 0;
    }

    int DeseaseDB::change_symptome(TObj<DeseaseName>* o, std::string n)
    {
        if (!n.empty())
            if (!find_symptome(n))
            {
                o->obj->set_name(n);
                return o->id;
            }
        return -1;
    }

    TObj<DeseaseName>* DeseaseDB::find_symptome(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = symptomes->find(t);
        delete t;
        return res;
    }

    // =============================
    // procedures table
    // =============================

    int DeseaseDB::add_procedure(std::string n)
    {
        return procedures->add_node(new DeseaseName(n));
    }

    int DeseaseDB::remove_procedure(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = procedures->remove(t);
        delete t;

        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_procedure(n);
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;
            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_procedure(int id)
    {
        TObj<DeseaseName>* res = procedures->at_pos(id);
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_procedure(res->obj->to_string());
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;
            procedures->remove_at(id);
            return 1;
        }
        return 0;
    }

    int DeseaseDB::change_procedure(TObj<DeseaseName>* o, std::string n)
    {
        if (!n.empty()) 
            if (!find_procedure(n))
            {
                o->obj->set_name(n);
                return o->id;
            }
        return -1;
    }

    TObj<DeseaseName>* DeseaseDB::find_procedure(std::string n)
    {
        DeseaseName* t = new DeseaseName(n);
        TObj<DeseaseName>* res = procedures->find(t);
        delete t;
        return res;
    }

    // =============================
    // threatment table
    // =============================

    int DeseaseDB::add_threatment(TObj<MedicineName>* m, int a)
    {
        return threatment->add_node(new Threatment(m, a));
    }

    int DeseaseDB::remove_threatment(TObj<MedicineName>* o, int a)
    {
        Threatment* t = new Threatment(o, a);
        TObj<Threatment>* res = threatment->remove(t);
        
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_threatment(res);
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;

            delete res->obj;
            delete res;
            return 1;
        }
        delete t;
        return 0;
    }

    int DeseaseDB::remove_threatment(int id)
    {
        
        TObj<Threatment>* res = threatment->at_pos(id);
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_threatment(res);
            
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);

            delete v;
            threatment->remove_at(id);
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_threatment(std::string n, int a)
    {
        MedicineName* m = new MedicineName(n);
        TObj<MedicineName>* o = new TObj<MedicineName>(m, 0);
        Threatment* t = new Threatment(o, a);
        TObj<Threatment>* res = threatment->remove(t);
        
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_threatment(res);
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;

            delete res->obj;
            delete res;
            return 1;
        }
        delete t;
        return 0;
    }
    int DeseaseDB::remove_threatment(TObj<Threatment>* t)
    {
        TObj<Threatment>* res = threatment->remove(t->obj);
        
        if (res)
        {
            std::vector<TObj<DeseaseDBEntry>*>* v = find_desease_by_threatment(res);
            if (v)
                for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_desease((*i)->obj);
            delete v;

            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::change_threatment(TObj<Threatment>* o, TObj<MedicineName>* n, int a)
    {
        if (a && !find_threatment(n, a))
        {
            o->obj->set_name(n);
            o->obj->set_amount(a);

            return o->id;
        }
        return -1;
    }


    TObj<Threatment>* DeseaseDB::find_threatment(TObj<MedicineName>* n, int a)
    {
        if (n)
        {
            Threatment* t = new Threatment(n, a);
            for (TObj<Threatment>* r = threatment->root(); r; r = r->next)
            {
                if (*r->obj == *t)
                    return r;
            }
        }
        return 0;
    }

    std::vector<TObj<Threatment>*>* DeseaseDB::find_threatment(TObj<MedicineName>* n)
    {
        if (n)
        {
            std::vector<TObj<Threatment>*>* vec = new  std::vector<TObj<Threatment>*>();
            for (TObj<Threatment>* r = threatment->root(); r; r = r->next)
            {
                if (r->obj->name()->obj->to_string() == n->obj->to_string())
                    vec->push_back(r);
            }
            if (vec->size())
            {
                return vec;
            }
            else
            {
                delete vec;
                return 0;
            }
        }
        return 0;
    }


    // =============================
    // desease table
    // =============================

    int DeseaseDB::add_desease(TObj<DeseaseName>* n, TObj<DeseaseName>* s, 
            TObj<DeseaseName>* p, TObj<Threatment>* t)
    {
        return desease_table->add_node(new DeseaseDBEntry(n, s, p, t));
    }

    int DeseaseDB::remove_desease(DeseaseDBEntry* o)
    {
        TObj<DeseaseDBEntry>* res = desease_table->remove(o);
        if (res)
        {
            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_desease(int id)
    {
        return desease_table->remove_at(id);
    }

    int DeseaseDB::change_desease(TObj<DeseaseDBEntry>* o, 
            TObj<DeseaseName>* n, TObj<DeseaseName>* s, 
            TObj<DeseaseName>* p, TObj<Threatment>* t)
    {
        if (n && s && p && t)
        {
            o->obj->name = n;
            o->obj->symptome = s;
            o->obj->procedure = p;
            o->obj->threatment = t;
            return o->id;
        }
        return -1;
    }

    TObj<DeseaseDBEntry>* DeseaseDB::find_desease(DeseaseDBEntry* o)
    {
        return desease_table->find(o);
    }

    TObj<DeseaseDBEntry>* DeseaseDB::find_desease(TObj<DeseaseName>* n, TObj<DeseaseName>* s, 
            TObj<DeseaseName>* p, TObj<Threatment>* t)
    {
        DeseaseDBEntry* d = new DeseaseDBEntry(n, s, p, t);
        TObj<DeseaseDBEntry>* res = desease_table->find(d);
        delete d;
        return res; 
    }

    std::vector<TObj<DeseaseDBEntry>*>* DeseaseDB::find_desease_by_name(std::string n)
    {
        std::vector<TObj<DeseaseDBEntry>*>* vec = new std::vector<TObj<DeseaseDBEntry>*>();
        for (TObj<DeseaseDBEntry>* r = desease_table->root(); r; r = r->next)
        {
            if (*(r->obj->name->obj->name()) == n)
                vec->push_back(r);
        }
        if (vec->size())
            return vec;
        else
        {
            delete vec;
            return 0;
        }
    }

    std::vector<TObj<DeseaseDBEntry>*>* DeseaseDB::find_desease_by_symptome(std::string n)
    {
        std::vector<TObj<DeseaseDBEntry>*>* vec = new std::vector<TObj<DeseaseDBEntry>*>();
        for (TObj<DeseaseDBEntry>* r = desease_table->root(); r; r = r->next)
        {
            if (*(r->obj->symptome->obj->name()) == n)
                 vec->push_back(r);
        }
        if (vec->size())
            return vec;
        else
        {
            delete vec;
            return 0;
        }
    }

    std::vector<TObj<DeseaseDBEntry>*>* DeseaseDB::find_desease_by_procedure(std::string n)
    {
        std::vector<TObj<DeseaseDBEntry>*>* vec = new std::vector<TObj<DeseaseDBEntry>*>();
        for (TObj<DeseaseDBEntry>* r = desease_table->root(); r; r = r->next)
        {
            if (*(r->obj->procedure->obj->name()) == n)
                vec->push_back(r);
        }
        if (vec->size())
            return vec;
        else
        {
            delete vec;
            return 0;
        }
    }

    std::vector<TObj<DeseaseDBEntry>*>* DeseaseDB::find_desease_by_threatment(TObj<Threatment>* t)
    {
        std::vector<TObj<DeseaseDBEntry>*>* vec = new std::vector<TObj<DeseaseDBEntry>*>();
        for (TObj<DeseaseDBEntry>* r = desease_table->root(); r; r = r->next)
        {
            if (*(r->obj->threatment->obj) == *(t->obj))
                vec->push_back(r);
        }
        if (vec->size())
        {
            return vec;
        }
        else
        {
            delete vec;
            return 0;
        }
    }

    std::vector<TObj<Threatment>*>* DeseaseDB::find_desease_threatment_by_name(std::string n)
    {
        std::vector<TObj<DeseaseDBEntry>*>* vec = find_desease_by_name(n);
        std::vector<TObj<Threatment>*>* res = new std::vector<TObj<Threatment>*>();
        if (vec)
        {
            for (std::vector<TObj<DeseaseDBEntry>*>::iterator i = vec->begin(); i != vec->end(); i++)
            {
                res->push_back((*i)->obj->threatment);
            }
            delete vec;
            return res;
        }
        else
            delete res;
        
        return 0;
    }

    // =============================
    // medicines table
    // =============================

    int DeseaseDB::add_medicine(std::string n)
    {
        return medicines->add_node(new MedicineName(n));
    }

    int DeseaseDB::remove_medicine(std::string n)
    {
        MedicineName* m = new MedicineName(n);
        TObj<MedicineName>* res = medicines->remove(m);    
        delete m;

        if (res)
        {
            if (TObj<MedicineDBEntry>* s = find_stock(n))
                remove_from_stock(s->obj);

            if (std::vector<TObj<MedicineAnalog>*>* v = find_analog(res))
            {
                for (std::vector<TObj<MedicineAnalog>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_analog((*i)->obj);
                delete v;
            }

            if (std::vector<TObj<MedicineAnalog>*>* v = find_analog_name(res))
            {
                for (std::vector<TObj<MedicineAnalog>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_analog((*i)->obj);
                delete v;
            }

            medicines->remove(m);

            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_medicine(int id)
    {
        TObj<MedicineName>* res = medicines->at_pos(id);    

        if (res)
        {
            if (std::vector<TObj<Threatment>*>* v = find_threatment(res))
            {
                for (std::vector<TObj<Threatment>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_threatment((*i));
            }

            if (TObj<MedicineDBEntry>* s = find_stock(*(res->obj->name())))
                remove_from_stock(s->obj);

            if (std::vector<TObj<MedicineAnalog>*>* v = find_analog(res))
            {
                for (std::vector<TObj<MedicineAnalog>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_analog((*i)->obj);
                delete v;
            }

            if (std::vector<TObj<MedicineAnalog>*>* v = find_analog_name(res))
            {
                for (std::vector<TObj<MedicineAnalog>*>::iterator i = v->begin(); i != v->end(); i++)
                    remove_analog((*i)->obj);
                delete v;
            }
            
            medicines->remove_at(id);

            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::change_medicine(TObj<MedicineName>* o, std::string n)
    {
        if (!n.empty())
        {
            std::cout << "here\n";
            if (!find_medicine(n))
            {
                o->obj->set_name(n);
                return o->id;
            }
        }
        return -1;
    } 

    TObj<MedicineName>* DeseaseDB::find_medicine(std::string n)
    {
        MedicineName* m = new MedicineName(n);
        TObj<MedicineName>* res = medicines->find(m);
        delete m;
        return res;
    }

    // =============================
    // stock table
    // =============================

    int DeseaseDB::add_to_stock(TObj<MedicineName>* m, int a)
    {
        return stock->add_node(new MedicineDBEntry(m ,a));
    }

    int DeseaseDB::remove_from_stock(MedicineDBEntry* n)
    {
        TObj<MedicineDBEntry>* res = stock->remove(n);
        if (res)
        {
            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_from_stock(int id)
    {
        return stock->remove_at(id);
    }

    int DeseaseDB::change_stock(TObj<MedicineDBEntry>* o, TObj<MedicineName>* n, int a)
    {
        TObj<MedicineDBEntry>* res = find_stock(n->obj->to_string());

        if (!res && n && a)
        {
            o->obj->set_name(n);
            o->obj->set_amount(a);
            return o->id;
        }
        else if (res->obj->amount() != a)
        {
            o->obj->set_amount(a);
            return o->id;
        }
    
        return -1;
    }
    
    TObj<MedicineDBEntry>* DeseaseDB::find_stock(TObj<MedicineName>* n)
    {
        for (TObj<MedicineDBEntry>* r = stock->root(); r; r = r->next)
        {
            if (*(r->obj->name()) == *n)
                return r;
        }
        return 0;
    }

    TObj<MedicineDBEntry>* DeseaseDB::find_stock(std::string n)
    {
        for (TObj<MedicineDBEntry>* r = stock->root(); r; r = r->next)
        {
            if (*(r->obj->name()->obj->name()) == n)
                return r;
        }
        return 0;
    }

    // =============================
    // analogs table
    // =============================

    int DeseaseDB::add_analog(TObj<MedicineName>* o, TObj<MedicineName>* a)
    {
        if (o != a)
            return analogs->add_node(new MedicineAnalog(o, a));
        else
            return 0;
    }


    int DeseaseDB::remove_analog(MedicineAnalog* m)
    {
        TObj<MedicineAnalog>* res = analogs->remove(m);
        if (res)
        {
            delete res->obj;
            delete res;
            return 1;
        }
        return 0;
    }

    int DeseaseDB::remove_analog(int id)
    {
        std::cout << id;
        return analogs->remove_at(id);
    }

    int DeseaseDB::change_analog(TObj<MedicineAnalog>* o, TObj<MedicineName>* n, TObj<MedicineName>* a)
    {
        if (o && n && a && !find_analog_entry(n->obj->to_string(), a->obj->to_string()))
        {
            o->obj->_name = n;
            o->obj->_analog = a;
            return o->id;
        }
        return -1;
    }

    std::vector<TObj<MedicineAnalog>*>* DeseaseDB::find_analog(TObj<MedicineName>* n)
    {
        std::vector<TObj<MedicineAnalog>*>* vec = new std::vector<TObj<MedicineAnalog>*>();
        for (TObj<MedicineAnalog>* r = analogs->root(); r; r = r->next)
        {
            if (*(r->obj->_analog) == *n)
                vec->push_back(r);
        }
        if (vec->size())
            return vec;
        else
        {
            delete vec;
            return 0;
        }
    }
    
    std::vector<TObj<MedicineAnalog>*>* DeseaseDB::find_analog_name(TObj<MedicineName>* n)
    {
        std::vector<TObj<MedicineAnalog>*>* vec = new std::vector<TObj<MedicineAnalog>*>();
        for (TObj<MedicineAnalog>* r = analogs->root(); r; r = r->next)
        {
            if (*(r->obj->_name) == *n)
                vec->push_back(r);
        }
        if (vec->size())
            return vec;
        else
        {
            delete vec;
            return 0;
        }
    }

    TObj<MedicineAnalog>* DeseaseDB::find_analog_entry(std::string n, std::string a)
    {
        for (TObj<MedicineAnalog>* r = analogs->root(); r; r = r->next)
        {
            if (r->obj->_name->obj->to_string() == n && r->obj->_analog->obj->to_string() == a)
                return r;
        }
        return 0;
    }

    // =============================
    // dump functions
    // =============================

    void DeseaseDB::dump()
    {
        
        if (!DirectoryExists(".\\db"))
            CreateDirectoryA(".\\db" , NULL);

        std::cout << "dump()\n";
        dump_names();
        dump_symptomes();
        dump_procedures();
        dump_threatment();
        dump_desease(); 
        dump_medicines();
        dump_stock();
        dump_analogs();

    }

    void DeseaseDB::recover()
    {
        if (DirectoryExists(".\\db"))
        {
            std::cout << "recover()\n";
            recover_names();
            recover_symptomes();
            recover_procedures();
            
            recover_medicines();
            
            recover_threatment();
            
            recover_desease();
            recover_stock();
            recover_analogs();
        }
    }
    
    

    // =============================
    // names
    // =============================

    void DeseaseDB::dump_names()
    {   
        std::ofstream file(".\\db\\names.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(names->counter());
            if (names->counter() && names->root())
                file <<  start_prop(true, "names", map);
            else
                file <<  start_prop(false, "names", map);
            map.erase("_counter");
            for (TObj<DeseaseName>* r = names->root(); r; r = r->next)
            {
                map["_name"] = r->obj->to_string();
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_names()
    {
        std::ifstream file(".\\db\\names.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "names")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);

                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    obj = next_pair(file);

                    if (names->add_node(new DeseaseName(obj["_name"])) != -1)
                        names->last()->id = std::stoi(prop);
                }
                names->set_counter(counter);
            }
            file.close();
        }
    }

    // =============================
    // symptomes
    // =============================

    void DeseaseDB::dump_symptomes()
    {   
        std::ofstream file(".\\db\\symptomes.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(symptomes->counter());
            if (symptomes->counter()  && symptomes->root())
                file <<  start_prop(true, "symptomes", map);
            else
                file <<  start_prop(false, "symptomes", map);
            map.erase("_counter");
            for (TObj<DeseaseName>* r = symptomes->root(); r; r = r->next)
            {
                map["_name"] = r->obj->to_string();
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_symptomes()
    {
        std::ifstream file(".\\db\\symptomes.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "symptomes")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    obj = next_pair(file);

                    if (symptomes->add_node(new DeseaseName(obj["_name"])) != -1)
                        symptomes->last()->id = std::stoi(prop);
                }
                symptomes->set_counter(counter);
            }
            file.close();
        }
    }
    

    // =============================
    // procedures
    // =============================

    void DeseaseDB::dump_procedures()
    {   
        std::ofstream file(".\\db\\procedures.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(procedures->counter());
            if (procedures->counter() && procedures->root())
                file <<  start_prop(true, "procedures", map);
            else
                file <<  start_prop(false, "procedures", map);
            map.erase("_counter");
            for (TObj<DeseaseName>* r = procedures->root(); r; r = r->next)
            {
                map["_name"] = r->obj->to_string();
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_procedures()
    {
        std::ifstream file(".\\db\\procedures.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "procedures")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    obj = next_pair(file);

                    if (procedures->add_node(new DeseaseName(obj["_name"])) != -1)
                        procedures->last()->id = std::stoi(prop);
                }
                procedures->set_counter(counter);
            }
            file.close();
        }
    }


    // =============================
    // threatment
    // =============================

    void DeseaseDB::dump_threatment()
    {   
        std::ofstream file(".\\db\\threatment.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(threatment->counter());
            if (threatment->counter()  && threatment->root())
                file <<  start_prop(true, "threatment", map);
            else
                file <<  start_prop(false, "threatment", map);
            map.erase("_counter");
            for (TObj<Threatment>* r = threatment->root(); r; r = r->next)
            {
                map["_amount"] = std::to_string(r->obj->amount());
                map["_nameid"] = std::to_string(r->obj->id());
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_threatment()
    {
        std::ifstream file(".\\db\\threatment.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "threatment")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    int amount = 0;
                    try
                    {
                        amount = std::stoi(next_pair(file).begin()->second);
                    } 
                    catch(...)
                    {
                        amount = 0;
                    }
                    int nameid = std::stoi(next_pair(file).begin()->second);
                    if (threatment->add_node(new Threatment(
                        medicines->at(nameid),
                        amount
                    )) != -1)
                        threatment->last()->id = std::stoi(prop);
                }
                threatment->set_counter(counter);
            }
            file.close();
        }
    }

    // =============================
    // desease
    // =============================

    void DeseaseDB::dump_desease()
    {   
        std::ofstream file(".\\db\\desease.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(desease_table->counter());
            if (desease_table->counter() && desease_table->root())
                file <<  start_prop(true, "desease", map);
            else
                file <<  start_prop(false, "desease", map);
            map.erase("_counter");
            for (TObj<DeseaseDBEntry>* r = desease_table->root(); r; r = r->next)
            {
                map["nameid"] = std::to_string(r->obj->nameid);
                map["symptomeid"] = std::to_string(r->obj->symptomeid);
                map["procedureid"] = std::to_string(r->obj->procedureid);
                map["threatmentid"] = std::to_string(r->obj->threatmentid);
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_desease()
    {
        std::ifstream file(".\\db\\desease.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "desease")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    TObj<DeseaseName>* n = names->at(std::stoi((next_pair(file))["nameid"]));
                    TObj<DeseaseName>* p = procedures->at(std::stoi((next_pair(file))["procedureid"]));
                    TObj<DeseaseName>* s = symptomes->at(std::stoi((next_pair(file))["symptomeid"]));
                    TObj<Threatment>* t = threatment->at(std::stoi((next_pair(file))["threatmentid"]));
                    
                    if (n && s && p && t)
                    {
                        if (desease_table->add_node(new DeseaseDBEntry(n, s, p, t)) != -1)
                            desease_table->last()->id = std::stoi(prop);
                    }
                }
                desease_table->set_counter(counter);
            }
            file.close();
        }
    }


    // =============================
    // medicines
    // =============================

    void DeseaseDB::dump_medicines()
    {   
        std::ofstream file(".\\db\\medicines.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(medicines->counter());
            if (medicines->counter() && medicines->root())
                file <<  start_prop(true, "medicines", map);
            else
                file <<  start_prop(false, "medicines", map);
            map.erase("_counter");
            for (TObj<MedicineName>* r = medicines->root(); r; r = r->next)
            {
                map["_name"] = r->obj->to_string();
                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_medicines()
    {
        std::ifstream file(".\\db\\medicines.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "medicines")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    obj = next_pair(file);

                    if (medicines->add_node(new MedicineName(obj["_name"])) != -1)
                        medicines->last()->id = std::stoi(prop);
                }
                medicines->set_counter(counter);
            }
            file.close();
        }
    }

    // =============================
    // stock
    // =============================

    void DeseaseDB::dump_stock()
    {   
        std::ofstream file(".\\db\\stock.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(stock->counter());
            if (stock->counter() && stock->root())
                file <<  start_prop(true, "stock", map);
            else
                file <<  start_prop(false, "stock", map);
            map.erase("_counter");
            for (TObj<MedicineDBEntry>* r = stock->root(); r; r = r->next)
            {
                map["_nameid"] = std::to_string(r->obj->id());
                map["_amount"] = std::to_string(r->obj->amount());

                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_stock()
    {
        std::ifstream file(".\\db\\stock.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "stock")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    int amount = 0;
                    try
                    {
                        amount = std::stoi(next_pair(file).begin()->second);
                    } 
                    catch(...)
                    {
                        amount = 0;
                    }
                    TObj<MedicineName>* m = medicines->at(std::stoi(next_pair(file).begin()->second));

                    if (m)
                    {
                        if (stock->add_node(new MedicineDBEntry(m, amount)) != -1)
                            stock->last()->id = std::stoi(prop);
                    }
                }
                stock->set_counter(counter);
            }
            file.close();
        }
    }

    // =============================
    // analogs
    // =============================

    void DeseaseDB::dump_analogs()
    {   
        std::ofstream file(".\\db\\analogs.json", std::ios_base::trunc);
        std::map<std::string, std::string> map;
        
        if (file.is_open())
        {
            file << "{\n";
            map["_counter"] = std::to_string(analogs->counter());
            if (analogs->counter() && analogs->root())
                file <<  start_prop(true, "analogs", map);
            else
                file <<  start_prop(false, "analogs", map);
            map.erase("_counter");
            for (TObj<MedicineAnalog>* r = analogs->root(); r; r = r->next)
            {
                map["nameid"] = std::to_string(r->obj->nameid);
                map["analogid"] = std::to_string(r->obj->analogid);

                file << obj_to_json(std::to_string(r->id), map, 2);
                if (r->next)
                    file << ",\n";
                else
                    file << "\n";

            }

            file << "\t}\n";
            file << "}";
            file.close();
        }
    }

    void DeseaseDB::recover_analogs()
    {
        std::ifstream file(".\\db\\analogs.json", std::ios_base::in);
        std::map<std::string, std::string> obj;
        std::string prop;
        int counter = 0;

        if (file.is_open())
        {
            if (!((prop = get_prop(file)).empty()) && prop == "analogs")
            {
                obj = next_pair(file);
                counter = std::stoi(obj["_counter"]);
                
                obj.erase("_counter");
                while ((prop = get_prop(file)).size())
                {
                    int analogid = std::stoi(next_pair(file).begin()->second);
                    int nameid = std::stoi(next_pair(file).begin()->second);

                    TObj<MedicineName>* a = medicines->at(analogid);
                    TObj<MedicineName>* n = medicines->at(nameid);

                    if (n && a)
                        if (analogs->add_node(new MedicineAnalog(n, a)) != -1)
                            analogs->last()->id = std::stoi(prop);
                }
                analogs->set_counter(counter);
            }
            file.close();
        }
    }

}