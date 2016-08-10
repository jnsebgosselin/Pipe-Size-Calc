#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QToolButton>
#include <QTextEdit>
#include "infowindow.h"

class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QLineEdit;

class MainWindow : public QWidget
{
 Q_OBJECT
public:
 explicit MainWindow(QWidget *parent = 0);
 void show();
private slots:
 void npsChanged();
 void showInfo();
private:
 bool *units;
 InfoWindow *qinfo;
 QLabel *qlogo;
 QLabel *qlabl1;
 QLabel *sdr_labl;
 QLabel *OD_labl;
 QLabel *ID_labl;
 QLabel *WT_labl;
 QComboBox *nps_widg;
 QDoubleSpinBox *sdr_widg;
 QTextEdit *OD_widg;
 QTextEdit *ID_widg;
 QTextEdit *WT_widg;
 QToolButton *nps_info;

 QLineEdit *HDB_widg;
 QLabel *HDB_labl;
 QLineEdit *BP_widg;
 QLabel *BP_labl;
 QLineEdit *PR_widg;
 QLabel *PR_labl;
 QComboBox *PE_widg;
 QLabel *PE_labl;

 QLabel *kp_labl;
 QTextEdit *kp_widg;
 QLabel *Rp_labl;
 QTextEdit *Rp_widg;
};

#endif // WINDOW_H
