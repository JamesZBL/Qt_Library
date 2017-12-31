#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // 连接数据库
  if(connectDatabase()){
      // 初始化 tableView
      initTableView();
    }
}

MainWindow::~MainWindow()
{
  delete ui;
}

/**
 * 会员注册
 *
 * @brief MainWindow::on_action_5_triggered
 */
void MainWindow::on_action_5_triggered()
{
  dlgAddReader = new AddReaderDialog(this);
  connect(dlgAddReader,&AddReaderDialog::addReader,this,&MainWindow::insertReader);
  dlgAddReader->exec();
}

/**
 * 打开 “关于” 对话框
 *
 * @brief MainWindow::on_action_8_triggered
 */
void MainWindow::on_action_8_triggered()
{
  dlgAbout = new AboutDialog(this);
  dlgAbout->exec();
}

/**
 * 打开 “添加图书” 对话框
 *
 * @brief MainWindow::on_action_triggered
 */
void MainWindow::on_action_triggered()
{
  dlgAddBook = new AddBookDialog(this);
  connect(dlgAddBook,&AddBookDialog::addBook,this,&MainWindow::insertBook);
  dlgAddBook->exec();
}

/**
 * 刷新列表
 *
 * @brief MainWindow::on_action_9_triggered
 */
void MainWindow::on_action_9_triggered()
{
  initTableView();
}

/**
 * 连接数据库
 *
 * @brief connect
 * @return
 */
bool MainWindow::connectDatabase()
{
  bool rslt = true;
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setPort(3306);
  db.setHostName("localhost");
  db.setUserName("root");
  db.setPassword("root");
  db.setDatabaseName("library_ks");
  if (!db.open()) {
      QMessageBox::information(0,QObject::tr("Error"),db.lastError().text());
      rslt = false;
    }
  return rslt;
}

/**
 * 初始化 TableView
 *
 * @brief MainWindow::initTableView
 */
void MainWindow::initTableView(){
  // 数据模型
  QSqlTableModel *model = new QSqlTableModel;
  model->setTable("tb_book");
  // 按编号排序
  model->setSort(0, Qt::AscendingOrder);
  // 编号
  model->setHeaderData(0,Qt::Horizontal,"Code");
  // 书名
  model->setHeaderData(1,Qt::Horizontal,"Name");
  // 库存
  model->setHeaderData(2,Qt::Horizontal,"Number");
  model->select();
  // 表格视图
  QTableView *view = ui->tableView;
  view->setModel(model);
  view->setColumnWidth(1,500);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  //  view->setColumnHidden(0, true);
  //  view->resizeColumnsToContents();
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // 表头
  QHeaderView *header = view->horizontalHeader();
  header->setStretchLastSection(true);
}

/**
 * 添加图书
 *
 * @brief MainWindow::insertBook
 * @param name 书名
 * @param number 册数
 * @return 执行结果
 */
bool MainWindow::insertBook(const QString name, const QString number){
  // 添加图书语句
  QSqlQuery query;
  QString sql("INSERT INTO tb_book VALUES(null,'"+name+"',"+number+")");
  qDebug() << sql;
  if(query.exec(sql)){
      // 执行成功
      QMessageBox::information(this,tr("Info"),tr("Insert Success"),QMessageBox::Yes);
    }else{
      // 执行失败
      QMessageBox::information(this,tr("Info"),tr("Invalid input"),QMessageBox::Yes);
      qDebug() << query.lastError().text();
    }

  // 刷新 tableView
  initTableView();
  return true;
}

/**
 * 删除选中图书
 *
 * @brief MainWindow::on_action_2_triggered
 */
void MainWindow::on_action_2_triggered()
{
  int row= ui->tableView->currentIndex().row();
  QAbstractItemModel *model = ui->tableView->model ();
  QModelIndex idIndex = model->index(row,0);
  QModelIndex nameIndex = model->index(row,1);
  QVariant idData = model->data(idIndex);
  QVariant nameData = model->data(nameIndex);
  if(QMessageBox::question(this,
                           "Info",
                           "Delete "+nameData.toString()+" ?",
                           QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
      deleteBook(idData.toString());
    }
}

/**
 * 删除图书
 *
 * @brief MainWindow::deleteBook
 * @param id 编码
 * @return
 */
bool MainWindow::deleteBook(const QString id){
  // 删除图书语句
  QSqlQuery query;
  QString sql("DELETE from tb_book where id = "+id);
  qDebug() << sql;
  if(query.exec(sql)){
      // 执行成功
      QMessageBox::information(this,tr("Info"),tr("Delete Success"),QMessageBox::Yes);
    }else{
      // 执行失败
      QMessageBox::information(this,tr("Info"),tr("Invalid input"),QMessageBox::Yes);
      qDebug() << query.lastError().text();
    }

  // 刷新 tableView
  initTableView();
  return true;
}

/**
 * 添加读者
 *
 * @brief MainWindow::insertReader
 * @param code 账号
 * @param name 姓名
 * @return
 */
bool MainWindow::insertReader(const QString code, const QString name){
  // 添加读者语句
  QSqlQuery query;
  QString sql("INSERT INTO tb_reader VALUES(null,'"+name+"',"+code+")");
  qDebug() << sql;
  if(query.exec(sql)){
      // 执行成功
      QMessageBox::information(this,tr("Info"),tr("Insert Success"),QMessageBox::Yes);
    }else{
      // 执行失败
      QMessageBox::information(this,tr("Info"),tr("Invalid input"),QMessageBox::Yes);
      qDebug() << query.lastError().text();
    }

  return true;
}
