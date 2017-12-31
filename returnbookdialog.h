#ifndef RETURNBOOKDIALOG_H
#define RETURNBOOKDIALOG_H

#include <QDialog>

namespace Ui {
  class ReturnBookDialog;
}

class ReturnBookDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ReturnBookDialog(QWidget *parent = 0);
  ~ReturnBookDialog();

private:
  Ui::ReturnBookDialog *ui;
};

#endif // RETURNBOOKDIALOG_H
