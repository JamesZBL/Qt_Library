#ifndef ADDREADERDIALOG_H
#define ADDREADERDIALOG_H

#include <QDialog>

namespace Ui {
  class AddReaderDialog;
}

class AddReaderDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddReaderDialog(QWidget *parent = 0);
  ~AddReaderDialog();

  void accept();

signals:
  void addReader(const QString code,const QString name);

private:
  Ui::AddReaderDialog *ui;
};

#endif // ADDREADERDIALOG_H
