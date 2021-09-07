#include "dialogaddproduct.h"
#include "ui_dialogaddproduct.h"

DialogAddProduct::DialogAddProduct(QWidget *parent,  QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::DialogAddProduct)
{
    ui->setupUi(this);
    m_db = db;
    ui->spinBox_startingInventory->setRange(0,50000);
    ui->spinBox_minimumRequired->setRange(0,50000);
}

DialogAddProduct::~DialogAddProduct()
{
    delete ui;
}

void DialogAddProduct::on_buttonBox_accepted()
{
    QSqlQuery q("INSERT INTO products (`ProductName`, `StartingInventory`, `MinimumRequired`) VALUES ('"
                + ui->lineEdit_productName->text() + "', " + ui->spinBox_startingInventory->text() + ", " + ui->spinBox_minimumRequired->text() + ")", m_db);
}
