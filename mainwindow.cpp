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
 * 借书
 *
 * @brief MainWindow::on_action_3_triggered
 */
void MainWindow::on_action_3_triggered()
{
  dlgLendBook = new LendBookDialog(this);
  connect(dlgLendBook,&LendBookDialog::lendBook,this,&MainWindow::lendBook);
  dlgLendBook->exec();
}

/**
 * 还书
 *
 * @brief MainWindow::on_action_4_triggered
 */
void MainWindow::on_action_4_triggered()
{
  dlgReturnBook = new ReturnBookDialog(this);
  connect(dlgReturnBook,&ReturnBookDialog::returnBook,this,&MainWindow::backBook);
  dlgReturnBook->exec();
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
 * 当前库存
 *
 * @brief MainWindow::on_action_6_triggered
 */
void MainWindow::on_action_6_triggered()
{
  sumRepertory();
}

/**
 * 已借总数
 *
 * @brief MainWindow::on_action_7_triggered
 */
void MainWindow::on_action_7_triggered()
{
  sumLend();
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
  db.setHostName("47.93.187.44");
  db.setUserName("library_ks");
  db.setPassword("library_ks");
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
  model->setHeaderData(0,Qt::Horizontal,tr("Book Code"));
  // 书名
  model->setHeaderData(1,Qt::Horizontal,tr("Book Name"));
  // 库存
  model->setHeaderData(2,Qt::Horizontal,tr("Number"));
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
  QString sql("INSERT INTO tb_book VALUES(null,'"+name.trimmed()+"',"+number.trimmed()+")");
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
                           tr("Info"),
                           tr("Are you sure to delete ")+nameData.toString()+" ?",
                           QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
      deleteBook(idData.toString());
    }
}

/**
 * 删除图书
 *
 * @brief MainWindow::deleteBook
 * @param id 编码
 * @return 执行结果
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
      QString e = query.lastError().text();
      if(e.contains("denied")){
          // 没有删除的权限
          QMessageBox::information(this,tr("Info"),tr("You don't have permission for deletion"),QMessageBox::Yes);
        }else{
          // 发生了错误
          QMessageBox::information(this,tr("Info"),tr("Error occured"),QMessageBox::Yes);
        }

      qDebug() << e;
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
 * @return 执行结果
 */
bool MainWindow::insertReader(const QString code, const QString name){
  // 添加读者语句
  QSqlQuery query;
  QString sql("INSERT INTO tb_reader VALUES(null,'"+name.trimmed()+"',"+code.trimmed()+")");
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

/**
 * 办理借书手续
 *
 * @brief MainWindow::lendBook
 * @param readerCode 会员账号
 * @param bookCode  图书编号
 * @return 执行结果
 */
bool MainWindow::lendBook(const QString readerCode, const QString bookCode){
  QSqlQuery queryBook;
  QSqlQuery queryBook2;
  QSqlQuery queryLend;
  QSqlQuery queryReader;

  QString sqlBook("SELECT number FROM tb_book WHERE id = "+bookCode);
  QString sqlQueryReader("SELECT * FROM tb_reader WHERE code = "+readerCode);

  queryBook.exec(sqlBook);
  int i(0);
  while(queryBook.next()){
      int number = queryBook.value(0).toInt();
      // 判断是否有库存
      if(number == 0){
          QMessageBox::information(this,tr("Info"),tr("No enough book"),QMessageBox::Yes);
          return false;
        }
      queryReader.exec(sqlQueryReader);
      // 判断输入的会员账号是否有效
      if(queryReader.size()<1){
          QMessageBox::information(this,tr("Info"),tr("Invalid reader id"),QMessageBox::Yes);
          return false;
        }
      i++;
    }

  if(i!=0){
      QString sqlLend("INSERT INTO tb_lend VALUES(null,"+bookCode.trimmed()+","+readerCode.trimmed()+",1,0)");
      QString sqlBook2("UPDATE tb_book SET number = number - 1 where id = "+bookCode.trimmed());

      qDebug() << sqlLend;
      qDebug() << sqlBook2;

      if(queryLend.exec(sqlLend)&&queryBook2.exec(sqlBook2)){
          // 执行成功
          QMessageBox::information(this,tr("Info"),tr("Lend Success"),QMessageBox::Yes);
        }else{
          // 执行失败
          QMessageBox::information(this,tr("Info"),tr("Error occured"),QMessageBox::Yes);
          qDebug() << queryLend.lastError().text();
        }
    }else{
      QMessageBox::information(this,tr("Info"),tr("No such book"),QMessageBox::Yes);
      return false;
    }


  initTableView();
  return true;
}

/**
 * 办理还书手续
 *
 * @brief MainWindow::backBook
 * @param readerCode
 * @param bookCode
 * @return 执行结果
 */
bool MainWindow::backBook(const QString readerCode, const QString bookCode){
  QSqlQuery queryLend;
  QSqlQuery queryBook;
  QSqlQuery queryBook2;
  QSqlQuery queryLend2;
  QString sqlLend("SELECT * FROM tb_lend WHERE book_id = "+bookCode+" AND reader_id = "+readerCode+" AND is_back = 0");
  qDebug() << sqlLend;

  if(queryLend.exec(sqlLend)){
      if(queryLend.size()<1){
          QMessageBox::information(this,tr("Info"),tr("No book lended"));
          return false;
        }
      else{
          while(queryLend.next()){
              QString bookId = queryLend.value(1).toString();
              QString id = queryLend.value(0).toString();
              QString sqlBook("UPDATE tb_book SET number = number + 1 WHERE id = "+bookId);
              qDebug() << sqlBook;
              if(!queryBook.exec(sqlBook)){
                  QMessageBox::information(this,tr("Info"),tr("Error occured when return book"));
                  return false;
                }else{
                  QString sqlLend2("UPDATE tb_lend SET is_back = 1 WHERE id = "+id);
                  QString sqlBook2("UPDATE tb_book SET number = number + 1 WHERE id ="+id);
                  qDebug() << sqlLend2;
                  qDebug() << sqlBook2;
                  queryBook2.exec(sqlBook2);
                  queryLend2.exec(sqlLend2);
                }
            }
        }
    }

  QMessageBox::information(this,tr("Info"),tr("Book returned success"));
  initTableView();
  return true;
}

/**
 * 统计所有图书的库存
 *
 * @brief MainWindow::sumRepertory
 */
void MainWindow::sumRepertory(){
  QSqlQuery querySumRepertory;
  QString sqlSumRepertory("SELECT SUM(number) FROM tb_book");
  querySumRepertory.exec(sqlSumRepertory);
  QString numberSum;
  while(querySumRepertory.next()){
      numberSum = querySumRepertory.value(0).toString();
    }

  QMessageBox::information(this,tr("Repertory"),tr("Current repertory: ")+numberSum+tr(""));
}

/**
 * 统计目前借出的总数
 *
 * @brief MainWindow::sumLend
 */
void MainWindow::sumLend(){
  QSqlQuery querySumLend;
  QString sqlLend("SELECT COUNT(*) FROM tb_lend WHERE is_back = 0");
  querySumLend.exec(sqlLend);
  QString numberSum;
  while(querySumLend.next()){
      numberSum = querySumLend.value(0).toString();
    }

  QMessageBox::information(this,tr("Repertory"),tr("Current lend sum: ")+numberSum+tr(""));
}

