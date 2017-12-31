#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>

namespace Ui {
  class AddBookDialog;
}

class AddBookDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddBookDialog(QWidget *parent = 0);
  ~AddBookDialog();

  void accept();

signals:
  void addBook(const QString name,const QString number);

private:
  Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
