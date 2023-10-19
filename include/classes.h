#ifndef CLASSES
#define CLASSES


namespace practice
{
    class DeseaseName // используется для названий, симптомов, процедур
    {
        std::string* _name;
    public:
        DeseaseName();
        DeseaseName(std::string);
        ~DeseaseName();

        std::string* name() const;
        void set_name(std::string);

        std::string to_string();
    };

    bool operator== (const DeseaseName&, const DeseaseName&);
    bool operator!= (const DeseaseName&, const DeseaseName&);

    class MedicineName : public DeseaseName // для названий лекарств(просто другой контекст)
    {
    public:
        MedicineName();
        MedicineName(std::string);
    };

    class MedicineDBEntry // для списка склада
    {
        TObj<MedicineName>* _name;
        int _nameid;
        int _amount;

    public:
        MedicineDBEntry();
        MedicineDBEntry(TObj<MedicineName>*, int);

        TObj<MedicineName>* name() const;
        int id() const;
        int amount() const;

        void set_name(TObj<MedicineName>*);
        void set_id(int);
        void set_amount(int);

        void add_amount(int);

        virtual std::string to_string();
        void checkid();
    };

    bool operator== (const MedicineDBEntry&, const MedicineDBEntry&);
    bool operator!= (const MedicineDBEntry&, const MedicineDBEntry&);

    class Threatment : public MedicineDBEntry // контекст рецептов
    {
    public:
        Threatment();
        Threatment(TObj<MedicineName>* , int);
    };

    bool operator== (const Threatment&, const Threatment&);
    bool operator!= (const Threatment&, const Threatment&);

    struct MedicineAnalog // список аналогов
    {
        TObj<MedicineName>* _name;
        TObj<MedicineName>* _analog;

        int nameid;
        int analogid;

        MedicineAnalog(TObj<MedicineName>* n, TObj<MedicineName>* a);

        TObj<MedicineName>* name() const;
        TObj<MedicineName>* analog() const;

        std::string to_string();
        void checkid();
    };

    bool operator== (MedicineAnalog&, MedicineAnalog&);
    bool operator!= (MedicineAnalog&, MedicineAnalog&);

    struct DeseaseDBEntry // список болезней
    {
        TObj<DeseaseName>* name;
        TObj<DeseaseName>* symptome;
        TObj<DeseaseName>* procedure;
        TObj<Threatment>* threatment;

        int nameid;
        int symptomeid;
        int procedureid;
        int threatmentid;

        DeseaseDBEntry(TObj<DeseaseName>* n, TObj<DeseaseName>* s,
            TObj<DeseaseName>* p, TObj<Threatment>* t);

        std::string to_string();
        void checkid();
    };

    bool operator== (DeseaseDBEntry&, DeseaseDBEntry&);
    bool operator!= (DeseaseDBEntry&, DeseaseDBEntry&);
}

#endif