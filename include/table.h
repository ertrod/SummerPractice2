#ifndef TABLE
#define TABLE

#include "practice.h"

namespace practice
{
    template<class T>
    struct TObj // структура для объектов таблицы, указатель на объект, указатели на следующий и предыдущий элементы
    {
        TObj<T>* next;
        TObj<T>* prev;

        T* obj;
        int id;

        TObj(T* o, int i) : obj(o), id(i), next(0), prev(0) { }

        bool operator== (TObj<T>& o);
        bool operator!= (TObj<T>& o);
    };

    // операции уместны так как они реализованы для каждлго класса
    template<class T>
    bool TObj<T>::operator==(TObj<T>& o) 
    {
        return *obj == *(o.obj);
    }
    template<class T>
    bool TObj<T>::operator!= (TObj<T>& o)
    {
        return *obj != *(o.obj);
    }

    // template of Table
    template<class T>
    class Table
    {
        int _counter;

        TObj<T>* _root;
        TObj<T>* _last;

        Table(const Table&) {}

    public:
        Table();
        Table(T* o);

        ~Table();

        // геттеры
        TObj<T>* root() const;
        TObj<T>* last() const;
        // сеттеры
        int counter() const;
        void set_counter(int);

        int add_node(T* o);
        
        TObj<T>* at(int id);
        TObj<T>* at_pos(int id); // получение позиции элемента

        void remove(int id);
        int remove_at(int id);
        TObj<T>* remove(T* o);

        int find_at(T* o); // получение позиции элемента

        TObj<T>* find(T* o);


        void reverse_table();

        void debug_print();
    };

    template<class T>
    Table<T>::Table() : _root(0), _last(0) { _counter = 0; }
    template<class T>
    Table<T>::Table(T* o) : Table()
    { 
        TObj<T>* t = new TObj<T>(o, _counter++);
        _root = t;
        _last = t;
    }

    template<class T>
    Table<T>::~Table()
    {
        if (_root)
        {
            TObj<T>* r;
            for (TObj<T>* r = 0; _root; _root = r)
            {
                r = _root->next;
                delete _root->obj;
                delete _root;
            }
        }
    }

    template<class T>
    TObj<T>* Table<T>::root() const { return _root; }
    template<class T>
    TObj<T>* Table<T>::last() const { return _last; }

    template<class T>
    int Table<T>::add_node(T* o)
    {
        TObj<T>* t;
        if (o)
            t = new TObj<T>(o, _counter++);
        else
            return - 1;

        if (!_root)
        {
            _root = t;
            _last = t;
            return t->id;
        }
        else
        {
            if (*t != *_root)
            {
                TObj<T>* r = _root;

                while(r->next)
                {
                    r = r->next;
                    if (*t == *r)
                    {
                        std::cout << t->obj->to_string() << " already exist in this table" << std::endl;
                        delete t;
                        t = 0;
                        return -1;
                    }
                }
                if (t)
                {
                    r->next = t;
                    t->prev = r;
                    _last = t;
                    
                    return t->id;
                }
            }
            else
            {
                std::cout << t->obj->to_string() << " already exist in this table" << std::endl;
                delete t;
            }
        }
        return -1;
    }

    template<class T>
    int Table<T>::counter() const { return _counter; }

    template<class T>
    void Table<T>::set_counter(int id)
    {
        _counter = id;
    }
    
    template<class T>
    TObj<T>* Table<T>::at(int id)
    {
        if (id >= 0 && id < _counter)
        {
            for (TObj<T>* r = _root; r; r = r->next)
            {
                if (r->id == id)
                {
                    return r;
                }   
            }
        }
        return 0;
    }

    template<class T>
    TObj<T>* Table<T>::at_pos(int id)
    {
        if (id >= 0 && id < _counter)
        {
            TObj<T>* r = _root;
            for (int i = id; i; r = r->next, i--)
                if (!r)
                    return 0;
            return r;
        }
        return 0;
    }

    template<class T>
    int Table<T>::remove_at(int id)
    {
        if (id >= 0 && id < _counter)
        {
            TObj<T>* r = _root;
            TObj<T>* p = r;
            
            for (int i = id; i && r;p = r, r = r->next, i--);

            if (r)
            { 
                if (*r == *_root)
                {
                    if (_root->next)
                    {
                        _root = _root->next;
                        _root->prev = 0;
                    }
                    else
                    {
                        _root = 0;
                        _last = 0;
                    }
                }
                else
                {
                    TObj<T>* prev = r->prev;
                    if (p && r->next)
                        p->next = r->next;
                    else if (p)
                        p->next = 0;
                    
                }

                delete r->obj;
                delete r;
                return 1;
            }
        }
        return 0;
    }

    template<class T>
    void Table<T>::remove(int id)
    {
        if (id >= 0 && id < _counter)
        {
            TObj<T>* r = _root;
            TObj<T>* p = r;
            
            for (; r; p = r, r = r->next)
            {
                if (r->id == id)
                {
                    if (_root->next)
                    {
                        _root = _root->next;
                        _root->prev = 0;
                    }
                    else
                    {
                        _root = 0;
                        _last = 0;
                    }
                }
                else
                {
                    TObj<T>* prev = r->prev;
                    if (p && r->next)
                        p->next = r->next;
                    else if (p)
                        p->next = 0;
                    
                }

                delete r->obj;
                delete r;
                
            }
        }
    }

    template<class T>
    int Table<T>::find_at(T* o)
    {
        for (TObj<T>* r = _root; r; r = r->next)
        {
            if (*(r->obj) == *o)
            {
                return r->id;
            }   
        }
        return -1;
    }

    template<class T>
    TObj<T>* Table<T>::find(T* o)
    {
        for (TObj<T>* r = _root; r; r = r->next)
        {
            if (*(r->obj) == *o)
            {
                return r;
            }   
        }
        return 0;
    }

    template<class T>
    TObj<T>* Table<T>::remove(T* o)
    {
        TObj<T>* p = 0;
        for (TObj<T>* r = _root; r; p = r, r = r->next)
        {
            // std::cout << "comp: " << r->obj->to_string() << " " << o->to_string() << std::endl;
            // std::cout << "comp: " << (*r->obj == *o) << std::endl;
            if (*(r->obj) == *o)
            {
                if (*r == *_root)
                {
                    if (_root->next)
                    {
                        _root = _root->next;
                        _root->prev = 0;
                    }
                    else
                    {
                        _root = 0;
                        _last = 0;
                    }
                }
                else
                {
                    TObj<T>* prev = r->prev;
                    if (p && r->next)
                        p->next = r->next;
                    else if (p)
                        p->next = 0;
                    
                }

                return r;
            }
        }
        return 0;
    }

    template<class T>
    void Table<T>::reverse_table()
    {
        TObj<T>* t = _root;
        _root = _last;
        _last = t;
    }

    template<class T>
    void Table<T>::debug_print()
    {
        if (_root)
            for (TObj<T>* r = _root; r; r = r->next)
            {
                if (r)
                    std::cout << r->id << " : " << r->obj->to_string() << std::endl;
            }
    }
}

#endif