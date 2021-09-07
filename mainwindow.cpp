#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    addConnection();

    showCurrentInventory();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    ui->dateEdit_fromFilterProducts->setCalendarPopup(true);
    ui->dateEdit_toFilterProducts->setCalendarPopup(true);
    ui->dateEdit_toFilterProducts->setDate(QDate::currentDate());
    ui->dateEdit_fromFilterProducts->setDate(QDate::currentDate().addYears(-1));
}

void MainWindow::addConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "in_mem_db");
    bool existed = QFile::exists("dbsqlite");
    db.setDatabaseName("dbsqlite");
    db.setHostName("host");
    db.setPort(1);
    if (!db.open()) QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while opening the connection"));

    if(!existed){
        //database file didn't exist
        QSqlQuery q("", db);
        q.exec("create table products (id integer primary key, ProductName varchar, StartingInventory integer, MinimumRequired integer)");
        q.exec("create table purchasers (id integer primary key, purchaser varchar)");
        q.exec("create table orders (id integer primary key, PurchaserId integer not null, ProductId integer not null, NumberShipped integer, OrderDate date, FOREIGN KEY (ProductId) REFERENCES products (id), FOREIGN KEY (PurchaserId) REFERENCES purchasers (id))");
        q.exec("create table suppliers (id integer primary key, supplier varchar)");
        q.exec("create table purchases (id integer primary key, SupplierId integer not null, ProductId integer not null, NumberReceived integer, PurchaseDate date, FOREIGN KEY (ProductId) REFERENCES products (id), FOREIGN KEY (SupplierId) REFERENCES suppliers (id))");

        q.exec("INSERT INTO `products` (`id`, `ProductName`, `StartingInventory`, `MinimumRequired`) "
               "VALUES "
                   "(1,'Dell Server',100007,15), "
                   "(2,'Book',100,20), "
                   "(3,'Cisco Router',45,88), "
                   "(4,'Keyboard',25,10), "
                   "(5,'Mouse',1,5), "
                   "(6,'Switch',5,1), "
                   "(7,'Monitor',0,0), "
                   "(8,'Case',10,10), "
                   "(9,'Headphones',500,400), "
                   "(10,'Multimeter',3,4), "
                   "(11,'Motherboard',0,0), "
                   "(12,'UniBox',200,300), "
                   "(13,'Desk',50,10), "
                   "(14,'Notebook',567,56467), "
                   "(15,'Chair',12,12), "
                   "(16,'test',500,25), "
                   "(17,'Firewalls',5,10), "
                   "(18,'Cables',9,100), "
                   "(19,'Test',25,222);");

        q.exec("INSERT INTO `purchasers` (`id`, `purchaser`) "
               "VALUES "
                   "(1,'AMD'), "
                   "(2,'IBM'), "
                   "(3,'Intel');");

        q.exec("INSERT INTO `orders` (`id`, `PurchaserId`, `ProductId`, `NumberShipped`, `OrderDate`) "
               "VALUES "
                   "(1,1,3,10,'2014-04-01'), "
                   "(2,3,3,20,'2014-04-22'), "
                   "(3,2,1,5,'2014-04-11'), "
                   "(4,1,3,10,'2014-04-02'), "
                   "(5,2,1,20,'2014-04-15'), "
                   "(6,3,3,3,'2014-02-22'), "
                   "(7,2,3,5,'2014-03-22'), "
                   "(8,1,3,10,'2014-01-22'), "
                   "(9,1,2,30,'2014-01-21'), "
                   "(10,3,3,5,'2014-04-23'), "
                   "(11,2,3,12,'2014-04-22'), "
                   "(12,1,2,124,'2014-04-22'), "
                   "(13,3,2,500,'2014-05-11'), "
                   "(14,1,5,5,'2015-04-07'), "
                   "(15,1,9,50,'2015-04-07'), "
                   "(16,2,3,1,'2015-04-07'), "
                   "(17,3,10,5,'2015-09-09'), "
                   "(18,1,10,12,'2016-02-05'), "
                   "(19,1,9,2,'2017-02-25'), "
                   "(20,1,9,1,'2017-01-15'), "
                   "(21,2,11,250,'2017-02-15'), "
                   "(22,3,16,14,'2017-04-05'), "
                   "(23,1,11,50,'2017-06-05'), "
                   "(24,1,9,200,'2017-06-05'), "
                   "(25,2,14,12,'2017-11-05'), "
                   "(26,1,17,900,'2017-04-05'), "
                   "(27,1,18,9000,'2017-06-05'), "
                   "(28,3,4,0,'2017-04-05');");

        q.exec("INSERT INTO `suppliers` (`id`, `supplier`) "
               "VALUES "
                   "(1,'ShockWave Tech'), "
                   "(2,'CDW'), "
                   "(3,'ACME Tech Supplies');");

        q.exec("INSERT INTO `purchases` (`id`, `SupplierId`, `ProductId`, `NumberReceived`, `PurchaseDate`) "
               "VALUES "
                   "(1,2,2,50,'2014-11-02'), "
                   "(2,2,1,15,'2014-09-02'), "
                   "(3,3,3,10,'2014-11-12'), "
                   "(4,2,2,25,'2014-01-02'), "
                   "(5,2,3,20,'2014-02-22'), "
                   "(6,1,1,5,'2015-11-02'), "
                   "(7,3,3,3,'2014-01-02'), "
                   "(8,1,3,20,'2015-11-11'), "
                   "(9,2,1,0,'2014-11-02'), "
                   "(10,1,1,5,'2016-11-02'), "
                   "(11,2,5,12,'2016-11-02'), "
                   "(12,2,3,90,'2016-11-02'), "
                   "(13,1,6,23,'2016-08-02'), "
                   "(14,2,10,25,'2017-11-02'), "
                   "(15,2,10,3,'2017-11-02'), "
                   "(16,1,10,0,'2017-01-02'), "
                   "(17,1,2,0,'2017-02-22'), "
                   "(18,2,1,10,'2017-03-02'), "
                   "(19,2,9,12,'2017-03-03'), "
                   "(20,2,13,1234,'2017-05-12'), "
                   "(21,1,12,0,'2017-05-22'), "
                   "(22,1,13,0,'2017-06-12'), "
                   "(23,2,3,0,'2017-08-02'), "
                   "(24,3,9,400,'2017-10-02'), "
                   "(25,1,14,0,'2017-11-02'), "
                   "(26,2,16,12,'2017-11-30'), "
                   "(27,1,3,0,'2017-07-02'), "
                   "(28,3,17,33,'2017-07-12'), "
                   "(29,1,18,453,'2017-07-23'), "
                   "(30,2,18,22,'2017-11-02');");
    }
}

void MainWindow::on_pushButton_currentInventory_clicked()
{
    showCurrentInventory();
    highlightNewActiveMenuButton(ui->pushButton_currentInventory);
}

void MainWindow::on_pushButton_incomingPurchases_clicked()
{
    showIncomingPurchases();
    highlightNewActiveMenuButton(ui->pushButton_incomingPurchases);
}

void MainWindow::on_pushButton_outgoingOrders_clicked()
{
    showOutgoingOrders();
    highlightNewActiveMenuButton(ui->pushButton_outgoingOrders);
}

void MainWindow::showCurrentInventory()
{
    ui->stackedWidget->setCurrentWidget(ui->page_currentInventory);

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_currentInventory);
    model->setQuery(QSqlQuery("SELECT products.productName 'Product Name', startingInventory 'Starting Inventory', "
                              "IFNULL((SELECT SUM(numberReceived) FROM purchases WHERE productId = products.id),0) 'Received', "
                              "IFNULL((SELECT SUM(numberShipped) FROM orders WHERE productId = products.id), 0) 'Shipped', "
                              "ioh 'Inventory On Hand', minimumRequired 'Minimum Required' FROM products "
                              "LEFT JOIN (SELECT productName, IFNULL( StartingInventory + "
                              "IFNULL((SELECT SUM(numberReceived) FROM purchases WHERE productId = products.id),0) - "
                              "IFNULL((SELECT SUM(numberShipped) FROM orders WHERE productId = products.id), 0), 0) AS 'IOH' "
                              "FROM products "
                              "LEFT JOIN purchases ON products.id = purchases.productId "
                              "LEFT JOIN orders ON products.id = orders.productId "
                              "GROUP BY productName) t ON products.productName = t.productName", db));
    ui->tableView_currentInventory->setModel(model);
    ui->tableView_currentInventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::showIncomingPurchases()
{
    ui->stackedWidget->setCurrentWidget(ui->page_incomingPurchases);

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_incomingPurchases);
    model->setQuery(QSqlQuery("SELECT PurchaseDate AS 'Purchase Date', ProductName AS 'Product Name', NumberReceived AS 'Number Received', Supplier AS 'Supplier Name' FROM purchases LEFT JOIN suppliers ON suppliers.id = purchases.SupplierId LEFT JOIN products ON products.id = purchases.ProductId ORDER BY ProductName ASC, PurchaseDate DESC", db));
    ui->tableView_incomingPurchases->setModel(model);
    ui->tableView_incomingPurchases->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::showOutgoingOrders()
{
    ui->stackedWidget->setCurrentWidget(ui->page_outgoingOrders);

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_outgoingOrders);
    model->setQuery(QSqlQuery("SELECT OrderDate AS 'Order Date', ProductName AS 'Product Name', NumberShipped AS 'Number Shipped', Purchaser AS 'Purchaser Name' FROM orders LEFT JOIN purchasers ON purchasers.id = orders.PurchaserId LEFT JOIN products ON products.id = orders.ProductId ORDER BY OrderDate DESC", db));
    ui->tableView_outgoingOrders->setModel(model);
    ui->tableView_outgoingOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::highlightNewActiveMenuButton(QPushButton *b)
{
    ui->pushButton_incomingPurchases->setStyleSheet(ui->pushButton_incomingPurchases->styleSheet().append("QPushButton {font-weight: normal}"));
    ui->pushButton_currentInventory->setStyleSheet(ui->pushButton_currentInventory->styleSheet().append("QPushButton {font-weight: normal}"));
    ui->pushButton_outgoingOrders->setStyleSheet(ui->pushButton_outgoingOrders->styleSheet().append("QPushButton {font-weight: normal}"));
    b->setStyleSheet(b->styleSheet().append("QPushButton {font-weight: bold}"));
}



void MainWindow::on_pushButton_addPurchase_clicked()
{
    QDialog *dialog = new DialogAddPurchase(this, db);
    dialog->exec();
    showIncomingPurchases();
}

void MainWindow::on_pushButton_addOrder_clicked()
{
    QDialog *dialog = new DialogAddOrder(this, db);
    dialog->exec();
    showOutgoingOrders();
}

void MainWindow::on_pushButton_addProduct_clicked()
{
    QDialog *dialog = new DialogAddProduct(this, db);
    dialog->exec();
    showCurrentInventory();
}

void MainWindow::on_pushButton_filterProducts_clicked()
{
    QString dateFrom = ui->dateEdit_fromFilterProducts->date().toString("yyyy-MM-dd");
    QString dateTo = ui->dateEdit_toFilterProducts->date().toString("yyyy-MM-dd");
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_currentInventory);
    model->setQuery(QSqlQuery("SELECT products.productName 'Product Name', "
                              "IFNULL((SELECT SUM(numberReceived) FROM purchases WHERE productId = products.id AND (purchaseDate BETWEEN '" + dateFrom + "' AND '" + dateTo + "')),0) 'Received', "
                              "IFNULL((SELECT SUM(numberShipped) FROM orders WHERE productId = products.id AND (orderDate BETWEEN '" + dateFrom + "' AND '" + dateTo + "')), 0) 'Shipped', "
                              "iohb 'Count Beginning', iohe 'Count End', minimumRequired 'Minimum Required' FROM products "
                              "LEFT JOIN (SELECT productName, IFNULL( StartingInventory + "
                              "IFNULL((SELECT SUM(numberReceived) FROM purchases WHERE productId = products.id AND purchaseDate <= date('" + dateTo + "')),0) - "
                              "IFNULL((SELECT SUM(numberShipped) FROM orders WHERE productId = products.id AND orderDate <= date('" + dateTo + "')), 0), 0) AS 'IOHE', "
                              "IFNULL( StartingInventory + "
                              "IFNULL((SELECT SUM(numberReceived) FROM purchases WHERE productId = products.id AND purchaseDate <= date('" + dateFrom + "')),0) - "
                              "IFNULL((SELECT SUM(numberShipped) FROM orders WHERE productId = products.id AND orderDate <= date('" + dateFrom + "')), 0), 0) AS 'IOHB' "
                              "FROM products "
                              "LEFT JOIN purchases ON products.id = purchases.productId "
                              "LEFT JOIN orders ON products.id = orders.productId "
                              "GROUP BY productName) t ON products.productName = t.productName", db));
    ui->tableView_currentInventory->setModel(model);
}

void MainWindow::on_pushButton_reverseFilter_clicked()
{
    showCurrentInventory();
}
