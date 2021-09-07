#include "dialogaddorder.h"
#include "ui_dialogaddorder.h"

DialogAddOrder::DialogAddOrder(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::DialogAddOrder)
{
    ui->setupUi(this);
    m_db = db;

    setDialogValues();
}

DialogAddOrder::~DialogAddOrder()
{
    delete ui;
}

void DialogAddOrder::setDialogValues()
{
    ui->dateEdit_outgoingOrders->setDate(QDate::currentDate());
    ui->dateEdit_outgoingOrders->setCalendarPopup(true);

    QSqlQueryModel *model = new QSqlQueryModel();

    // fill combobox products
    model->setQuery("SELECT ProductName, id FROM products", m_db);
    for (int i = 0; i < model->rowCount();i++) {
        products[model->record(i).value(0).toString()] = model->record(i).value(1).toInt();
        ui->comboBox_orderProducts->addItem(model->record(i).value(0).toString());
    }

    // fill combobox purchasers
    model->setQuery("SELECT Purchaser, id FROM purchasers", m_db);
    for (int i = 0; i < model->rowCount();i++) {
        purchasers[model->record(i).value(0).toString()] = model->record(i).value(1).toInt();
        ui->comboBox_purchasers->addItem(model->record(i).value(0).toString());
    }
}

void DialogAddOrder::on_buttonBox_accepted()
{
    int purchaserId = purchasers.find(ui->comboBox_purchasers->currentText())->second;
    int productId = products.find(ui->comboBox_orderProducts->currentText())->second;

    QSqlQuery q("INSERT INTO orders (`PurchaserId`, `ProductId`, `NumberShipped`, `OrderDate`) VALUES ("
                + QString::number(purchaserId) + ", " + QString::number(productId) + ", " + ui->spinBox_numberShipped->text() + ", '" + ui->dateEdit_outgoingOrders->date().toString("yyyy-MM-dd") + "')", m_db);
    q.exec("UPDATE products SET InventoryShipped = (SELECT InventoryShipped FROM products WHERE id = " + QString::number(productId) + ") + " + ui->spinBox_numberShipped->text() + ", "
           "InventoryOnHand = (SELECT InventoryOnHand FROM products WHERE id = " + QString::number(productId) + ") - " + ui->spinBox_numberShipped->text() + " WHERE id = " + QString::number(productId));
}
