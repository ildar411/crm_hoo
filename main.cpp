#include "widget.h"
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <iostream>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
using namespace std;
enum flag {y = 1, n =2 };
ostream& operator << (ostream &stream, const QString &str)
{
    return stream << str.toStdString();
}
istream& operator >> (istream &stream, const QString& str)
{
    stream >> str;
    return stream;
}
/*istream& operator >> (istream &stream, const flag& n)
{
    QString a;
    stream >> a;
    if(a == "y")
        return stream;
    else
        return 2;
}*/

class DB_interaction {
public:
    void add_on_stock_trade_unit(int, QString, QString);//добавление на продажу ivan tz
    void Stock_Unit_add(int, QDate);//ivan tz
    void Stock_Type_Price_add(double, QDate);//ivan tz
    DB_interaction();//подумать над разными конструкторами этого класса must have
    ~DB_interaction();//деструктор must have
    QSqlDatabase crmDB;
private:
    int Stock_Trade_unit_id;

    
};
void DB_interaction::Stock_Type_Price_add(double price, QDate date_start)
{
    QSqlQuery query;
    cin >> price;
    date_start = QDate::currentDate();
    query.prepare("insert into Stock_Type_Price(price, date_start, Stock_Trade_unit_id)"
                  "values(?, ?, ?)");
    query.addBindValue(price);
    query.addBindValue(date_start);
    query.addBindValue(Stock_Trade_unit_id);
    query.exec();

}

DB_interaction::DB_interaction()
{
    crmDB = QSqlDatabase::addDatabase("QMYSQL", "CRM_ivan_1.2");
    bool ok = crmDB.open();
    if (ok == false)
        exit(-1);


}
void DB_interaction::Stock_Unit_add(int quantity, QDate date_add)
{
    QSqlQuery query;
    cin >> quantity;
    date_add = QDate::currentDate();
    query.prepare("insert into Stock_Unit(date_add, Stock_Trade_unit_id, quantity)"
                  "values(?, ?, ?)");
    query.addBindValue(quantity);
    query.addBindValue(Stock_Trade_unit_id);
    query.addBindValue(date_add);
    query.exec();
} 
void DB_interaction::add_on_stock_trade_unit(int type_id, QString trademark, QString tradeunit/*, flag sample_flag*/)
{
   QSqlQuery query;
   QSqlQueryModel model;
   cin >> type_id;
   cin >> trademark;
   cin >> tradeunit;
  // cin >> sample_flag;
   query.prepare("insert into Stock_Trade_Unit(type, trademark, tradeunit)"
              "values(?, ?, ?, ?)");
   query.addBindValue(type_id);
   query.addBindValue(trademark);
   query.addBindValue(tradeunit);
  // query.addBindValue(sample_flag);
   query.exec();
   model.setQuery("select id from Stock_Trade_Unit");
   for(int i = 0; i < model.rowCount(); ++i)
   {
       if(model.record(i).value("trademark") == trademark && model.record(i).value("tradeunit") == tradeunit)
           Stock_Trade_unit_id = model.record(i).value("id").toInt();

   }
}
class empl
{
public:
    void add_employee(QString, QString, QString, QDate);
    void del_employee(QString, QString, QString, QDate);
private:
    int Status_id;
};
void empl::add_employee(QString name, QString surname, QString patronymic, QDate date_hired)
{
    QSqlQuery query;
    cin >> name;
    cin >> surname;
    cin >> patronymic;
    date_hired = QDate::currentDate();
    query.prepare("insert into Employee(name, surname, patronymic, date_hired"
                  "values(?, ?, ?, ?, ?");
    query.addBindValue(name);
    query.addBindValue(surname);
    query.addBindValue(patronymic);
    query.addBindValue(date_hired);
    query.exec();



}
void empl::del_employee(QString name, QString surname, QString patronymic, QDate date_fired)
{
    QSqlQuery query;
    cin >> name;
    cin >> surname;
    date_fired = QDate::currentDate();
    query.prepare("insert into (select date_fired from Employee where name = ?, surname = ?) (date_fired)"
                  "values(?) ");

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    QSqlDatabase crmDB;
    crmDB = QSqlDatabase::addDatabase("QMYSQL", "CRM_Stock_realisation");


    int a_type; //прототип add_on_stock идет до query.exec();
    QString a_trademark;
    QString a_tradeunit;
    QSqlQuery query;
    cin >> a_type;
    cin >> a_trademark;
    cin >> a_tradeunit;
    query.prepare("insert into Stock_Trade_Unit(type, trademark, tradeunit)"
               "values(?, ?, ?)");
    query.addBindValue(a_type);
    query.addBindValue(a_trademark);
    query.addBindValue(a_tradeunit);
    query.exec();

    return a.exec();
}
