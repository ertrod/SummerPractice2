#ifndef DATABASE
#define DATABASE

#include "practice.h"

namespace practice
{
    // по названиям понятно
    class DeseaseDB
    {
        Table<DeseaseName>* names;
        Table<DeseaseName>* symptomes;
        Table<DeseaseName>* procedures;
        Table<Threatment>* threatment;

        Table<DeseaseDBEntry>* desease_table;

        Table<MedicineName>* medicines;
        Table<MedicineDBEntry>* stock;

        Table<MedicineAnalog>* analogs;

        void dump_names();
        void recover_names();

        void dump_symptomes();
        void recover_symptomes();

        void dump_procedures();
        void recover_procedures();

        void dump_threatment();
        void recover_threatment();
        
        void dump_desease();
        void recover_desease();
        
        void dump_medicines();
        void recover_medicines();
        
        void dump_stock();
        void recover_stock();
        
        void dump_analogs();
        void recover_analogs();

    public:
        DeseaseDB();
        ~DeseaseDB(); 

        void dump();
        void recover();

        Table<DeseaseName>* names_table();
        Table<DeseaseName>* symptomes_table();
        Table<DeseaseName>* procedures_table();
        Table<Threatment>* threatment_table();

        Table<DeseaseDBEntry>* deseasedb_table();

        Table<MedicineName>* medicines_table();
        Table<MedicineDBEntry>* stock_table();

        Table<MedicineAnalog>* analogs_table();

        int add_name(std::string);
        int remove_name(std::string);
        int remove_name(int);
        int change_name(TObj<DeseaseName>*, std::string);
        TObj<DeseaseName>* find_name(std::string);

        int add_symptome(std::string);
        int remove_symptome(std::string);
        int remove_symptome(int);
        int change_symptome(TObj<DeseaseName>*, std::string);
        TObj<DeseaseName>* find_symptome(std::string);

        int add_procedure(std::string);
        int remove_procedure(std::string);
        int remove_procedure(int);
        int change_procedure(TObj<DeseaseName>*, std::string);
        TObj<DeseaseName>* find_procedure(std::string);

        int add_threatment(TObj<MedicineName>*, int);
        int remove_threatment(std::string, int);
        int remove_threatment(TObj<MedicineName>*, int);
        int remove_threatment(int);
        int remove_threatment(TObj<Threatment>*);
        int change_threatment(TObj<Threatment>*, TObj<MedicineName>*, int);
        TObj<Threatment>* find_threatment(TObj<MedicineName>*, int);
        std::vector<TObj<Threatment>*>* find_threatment(TObj<MedicineName>*);

        int add_desease(TObj<DeseaseName>*, TObj<DeseaseName>*, 
            TObj<DeseaseName>*, TObj<Threatment>*);
        int remove_desease(DeseaseDBEntry*);
        int remove_desease(int);
        int change_desease(TObj<DeseaseDBEntry>*, TObj<DeseaseName>*, TObj<DeseaseName>*, 
            TObj<DeseaseName>*, TObj<Threatment>*);
        TObj<DeseaseDBEntry>* find_desease(DeseaseDBEntry*);
        TObj<DeseaseDBEntry>* find_desease(TObj<DeseaseName>*, TObj<DeseaseName>*, 
            TObj<DeseaseName>*, TObj<Threatment>*);
        std::vector<TObj<DeseaseDBEntry>*>* find_desease_by_name(std::string);
        std::vector<TObj<DeseaseDBEntry>*>* find_desease_by_symptome(std::string);
        std::vector<TObj<DeseaseDBEntry>*>* find_desease_by_procedure(std::string);
        std::vector<TObj<DeseaseDBEntry>*>* find_desease_by_threatment(TObj<Threatment>*);
        std::vector<TObj<Threatment>*>* find_desease_threatment_by_name(std::string);

        int add_medicine(std::string);
        int remove_medicine(std::string);
        int remove_medicine(int);
        int change_medicine(TObj<MedicineName>*, std::string);
        TObj<MedicineName>* find_medicine(std::string);

        int add_to_stock(TObj<MedicineName>*, int);
        int remove_from_stock(MedicineDBEntry*);
        int remove_from_stock(int);
        int change_stock(TObj<MedicineDBEntry>*, TObj<MedicineName>*, int);
        TObj<MedicineDBEntry>* find_stock(TObj<MedicineName>*);
        TObj<MedicineDBEntry>* find_stock(std::string);

        int add_analog(TObj<MedicineName>*, TObj<MedicineName>*);
        int remove_analog(MedicineAnalog*);
        int remove_analog(int);
        int change_analog(TObj<MedicineAnalog>*, TObj<MedicineName>*, TObj<MedicineName>*);
        std::vector<TObj<MedicineAnalog>*>* find_analog(TObj<MedicineName>*);
        std::vector<TObj<MedicineAnalog>*>* find_analog_name(TObj<MedicineName>*);
        TObj<MedicineAnalog>* find_analog_entry(std::string, std::string);
    };

}

#endif