#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QToolButton>
#include <QTextEdit>

class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QTextBrowser;

class InfoWindow : public QWidget
{
 Q_OBJECT
public:
 explicit InfoWindow(QWidget *parent = 0);
 QTextBrowser *qtext;
 void firstShow();
private:
 bool *units; 
};

#endif // INFOWINDOW_H
