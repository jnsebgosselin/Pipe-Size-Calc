/******************************************************************************
copyright 2016 Jean-Sébastien Gosselin
email: jean-sebastien.gosselin@ete.inrs.ca

Pipe Size Calc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it /will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QList>
#include <QtGui>
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QToolButton>
#include <QTextEdit>
#include <QRect>
#include <QPoint>
#include <QDesktopWidget>
#include <QTextBrowser>
#include <QEventLoop>

#include "mainwindow.h"
#include "infowindow.h"

#include <vector>
#include <iostream>
//using namespace std;
#include <algorithm>    // std::min

QString version("0.2");

std::vector<std::string> IPS = {"1/2", "3/4", "1", "1 1/4", "1 1/2", "2",
                                "2 1/2", "3", "3 1/2", "4", "5", "6", "8" ,
                                "10", "12", "14", "16", "18"};

std::vector<double> OD = {0.840, 1.050, 1.315, 1.660, 1.900, 2.375, 2.875,
                          3.500, 4.000, 4.500, 5.563, 6.625, 8.625, 10.750,
                          12.750, 14.000, 16.000, 18.000};

std::vector<double> ODtol = {0.004, 0.004, 0.005, 0.005, 0.006, 0.006, 0.007,
                             0.008, 0.009, 0.009, 0.011, 0.011, 0.013, 0.015,
                             0.017, 0.063, 0.072, 0.081};

std::vector<std::string> PE = {"PE1404", "PE2708", "PE3608", "PE4608",
                               "PE4710"};
std::vector<double> HDS23 = {400, 800, 800, 800, 1000};
std::vector<double> ATS = {1250, 2520, 2900, 2900, 2900};

int main(int argv, char **args)
{
    QApplication app(argv, args);

    QFont nf("Segoe UI", 11);
    QApplication::setFont(nf);

    MainWindow *window = new MainWindow;
    window->show();
    return app.exec();
}

// ============================================================================
InfoWindow::InfoWindow(QWidget *parent) :
  QWidget(parent)
// ============================================================================
{
    this->setWindowIcon(QIcon(":/resources/versalogo.png"));
    this->setWindowTitle("About");
    this->setWindowFlags(Qt::Window);

    qtext = new QTextBrowser;
    qtext->setReadOnly(true);
    qtext->setOpenExternalLinks(true);
    qtext->setFixedWidth(650);
    qtext->setFrameStyle(0);

    QString lic = "";

    lic += "<style>";
    lic += "p{font-size: 14px; margin-right: 10px; margin-left: 10px;}";
    lic += "</style>";

    lic += "<h1 align=center>";
    lic += "Pipe Size Calc<br>Version " + version;
    lic += "</h1>";

    lic += "<p align=center>Copyright 2016 ";
    lic += "";
    lic += "Jean-S&eacute;bastien Gosselin<br>";
    lic += "jean-sebastien.gosselin@ete.inrs.ca";
    lic += "</p>";

    lic += "<p align=center>";
    lic += "<b>Versaprofiles</b><br>";
    lic += "Saint-Lazare de Bellechasse, Qc, Canada<br>";
    lic += "<a href='http://www.versaprofiles.com/en'>";
    lic += "(http://www.versaprofiles.com)</a>";
    lic += "<p>";

    lic += "<p align=center>";
    lic += "<b>Institut National de la Recherche Scientifique</b><br>";
    lic += "Research Center Eau Terre Environnement, Quebec City, Qc, ";
    lic += "Canada<br><a href='http://www.ete.inrs.ca/'>";
    lic += "(http://www.ete.inrs.ca)</a>";
    lic += "<p>";

    lic += "<p align=justify>";
    lic += "<b>Pipe Size Calc</b> is free software: you can redistribute it ";
    lic += "and/or modify it under the terms of the GNU General Public ";
    lic += "License as published by the Free Software Foundation, either ";
    lic += "version 3 of the License, or (at your option) any later version.";
    lic += "</p>";

    lic += "<p align=justify>";
    lic += "This program is distributed in the hope that it will be ";
    lic += "useful, but WITHOUT ANY WARRANTY; without even the ";
    lic += "implied warranty of MERCHANTABILITY or FITNESS FOR A ";
    lic += "PARTICULAR PURPOSE. See the GNU General Public License ";
    lic += "for more details.";
    lic += "</p>";

    lic += "<p align=justify>";
    lic += "You should have received a copy of the GNU General";
    lic += "Public License along with this program.  If not, see ";
    lic += "<a href='http://www.gnu.org/licenses'>";
    lic += "http://www.gnu.org/licenses</a>.";
    lic += "<p>";

    lic += "<p align=right>2016/08/04</p>";

    qtext->setHtml(lic);

    QGridLayout *qgrid = new QGridLayout;
    qgrid->addWidget(qtext, 0, 0);

    this->setLayout(qgrid);
}

void InfoWindow::firstShow()  // --------------------------------- first show -
{
    this->setAttribute (Qt::WA_DontShowOnScreen, true) ;
    this->show();

    QEventLoop EventLoop (this) ;
    for (int i = 0 ; i < 10 ; i++)
        if (!EventLoop.processEvents()) break ;

    int hw = this->sizeHint().height();
    int ht = this->qtext->sizeHint().height();
    int hd = this->qtext->document()->size().height();

    this->setFixedSize(this->size().width(), hd + hw - ht);

    QRect qr = this->frameGeometry();
    int wp = this->parentWidget()->frameGeometry().width();
    int hp = this->parentWidget()->frameGeometry().height();
    QPoint cp = this->parentWidget()->mapToGlobal(QPoint(wp/2, hp/2));
    qr.moveCenter(cp);

    this->move(qr.topLeft());

    this->hide();
    this->setAttribute (Qt::WA_DontShowOnScreen, false) ;
}

// ============================================================================
MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent)
// ============================================================================
{
    this->setWindowIcon(QIcon(":/resources/versalogo.png"));
    this->setWindowTitle("Pipe Size Calculator v" + version);

    units = new bool(1);
    qinfo = new InfoWindow(this);

    //------------------------------------------------------------- NPS & SDR -

    QString tp;
    tp = "<p>The Dimension Ratio (DR) is the ratio of the pipe ";
    tp += "outside diameter (OD) to the minimum wall thickness ";
    tp += "(t<sub>min</sub>) and can be expressed as:</p>";
    tp += "<p align=center>DR = OD / t<sub>min</sub></p>";
    tp += "<p>The pressure rating is uniform for all nominal sizes of pipe ";
    tp += "for a given PE pipe material and DR.</p>";

    qlabl1 = new QLabel("Iron Pipe Size (IPS) :");
    nps_widg = new QComboBox;

    for (std::size_t i = 0, max = IPS.size(); i != max; ++i)
    {
        nps_widg->addItem(IPS[i].c_str());
    }

    sdr_labl = new QLabel("Dimension Ratio (DR) :");
    sdr_labl->setToolTip(tp);
    sdr_widg = new QDoubleSpinBox;
    sdr_widg->setValue(11);
    sdr_widg->setMinimum(7);
    sdr_widg->setSingleStep(0.5);
    sdr_widg->setToolTip(tp);

    nps_info = new QToolButton;
    nps_info->setIconSize(QSize(24, 24));
    nps_info->setAutoRaise(true);
    nps_info->setIcon(QIcon(":/resources/info.png"));
    nps_info->setToolTip("Show Copyrights and Licensing information");

    //-------------------------------------------------------------------- OD -

    tp = "<p>The outside diameters are specified as in Table 2 of:";
    tp += "<p><i>";
    tp += "ANSI B36.10-1979: American National Standard for Welded and ";
    tp += "Seamless Wrought Steel Pipe.";
    tp += "</i></p>";

    tp += "<p>The outside diameter tolerances are specified as in ";
    tp += "Table 2 of:<p>";

    tp += "<p><i>";
    tp += "ASTM D3035-15: Standard Specification for Polyethylene (PE) ";
    tp += "Plastic Pipe (DR-PR) Based on Controlled Outside Diameter.";
    tp += "</i></p>";

    tp += "The outside diameters and tolerances for the IPS values not ";
    tp += "listed in Table 2 of ASTM D3035-1 (2 1/2, 3 1/2, and 5) ";
    tp += "are specified such that their tolerances correspond to the same ";
    tp += "percentage of the outside diameter as those for the closest ";
    tp += "listed diameter.</p>";

    OD_labl = new QLabel("Outside Diameter (OD) :");
    OD_labl->setToolTip(tp);

    OD_widg = new QTextEdit;
    OD_widg->setReadOnly(true);
    OD_widg->setToolTip(tp);

    //-------------------------------------------------------------------- ID -

    tp = "<p>The inside diameter is calculated from the outside diameter ";
    tp += "and the average wall tickness, such as:";
    tp += "<p align=center>ID = OD - (2 x t<sub>avg</sub>)</p>";
    tp += "<p>where:</p>";
    tp += "<p align=center>t<sub>avg</sub> = t<sub>min</sub> + tol/2</p>";

    ID_labl = new QLabel("Inside Diameter (ID) :");
    ID_labl->setToolTip(tp);

    ID_widg = new QTextEdit;
    ID_widg->setReadOnly(true);
    ID_widg->setToolTip(tp);

    //-------------------------------------------------------------------- WT -

    tp = "<p>The minimum is the lowest wall thickness of the pipe at ";
    tp += "any cross section and is calculated with:</p>";
    tp += "<p align=center>t<sub>min</sub> = OD / DR</p>";
    tp += "<p> The maximum permitted wall thickness, at any cross section, ";
    tp += "is the minimum wall thickness plus the stated tolerance, such as:";
    tp += "<p align=center>t<sub>max</sub> = t<sub>min</sub> + tol</p>";
    tp += "All tolerances are on the plus side of the minimum requirement ";
    tp += "and equal 12% of the minimum wall thickness such as:</p>";
    tp += "<p align=center>tol = 0.12 * t<sub>min</sub></p>";
    tp += "<p>The lowest permitted wall thickness is 0.060 in., while the ";
    tp += "lowest permitted tolerance is 0.020 in.";

    WT_labl = new QLabel("Min. Wall Thickness (t<sub>min</sub>) :");
    WT_labl->setToolTip(tp);

    WT_widg = new QTextEdit;
    WT_widg->setReadOnly(true);
    WT_widg->setToolTip(tp);

    //-------------------------------------------------------------------- PE -

    PE_labl = new QLabel("PE Pipe Material :");
    PE_widg = new QComboBox;

    for (std::size_t i = 0, max = PE.size(); i != max; ++i)
    {
        PE_widg->addItem(PE[i].c_str());
    }

    //-------------------------------------------------------------------- BP -

    tp = "<p>Burst pressure (BP) requirements for water at 73°F (23°C) for ";
    tp += "DR-PR PE plastic pipe. BP is calculated with:</p>";
    tp += "<p align=center>BP = 2*σ<sub>y</sub> / (DR-1)</p>";
    tp += "<p>where σ<sub>y</sub> is the tensile strength at yield of the ";
    tp += "PE pipe material, whose values are specified as in Table 5 of:<p>";
    tp += "<p><i>";
    tp += "ASTM D3035-15: Standard Specification for Polyethylene (PE) ";
    tp += "Plastic Pipe (DR-PR) Based on Controlled Outside Diameter.";
    tp += "</i></p>";

    BP_labl = new QLabel("Min. Burst Pressure (BP) :");
    BP_labl->setToolTip(tp);

    BP_widg = new QLineEdit;
    BP_widg->setReadOnly(true);
    BP_widg->setToolTip(tp);
    BP_widg->setAlignment(Qt::AlignHCenter);

    //-------------------------------------------------------------------- PR -

    tp = "<p>Water pressure ratings (PR) at 73°F (23°C) for ";
    tp += "DR-PR PE plastic pipe. PR is calculated with</p>";
    tp += "<p align=center>PR = 2*HDB / (DR-1)</p>";
    tp += "<p>where HDB is the hydrostatic design stress for water at ";
    tp += "73°F (23°C). Values of HDB for the PE materials are specified as ";
    tp += "in Table 1 of:<p>";
    tp += "<p><i>";
    tp += "ASTM D3035-15: Standard Specification for Polyethylene (PE) ";
    tp += "Plastic Pipe (DR-PR) Based on Controlled Outside Diameter.";
    tp += "</i></p>";

    PR_labl = new QLabel("Pressure Rating (PR) :");
    PR_labl->setToolTip(tp);

    PR_widg = new QLineEdit;
    PR_widg->setReadOnly(true);
    PR_widg->setToolTip(tp);
    PR_widg->setAlignment(Qt::AlignHCenter);

    //------------------------------------------------------------------ Logo -

    QPixmap mypix (":/resources/VersaProfiles_Horizontal_COUL.png");
    qlogo = new QLabel;
    qlogo->setPixmap(mypix);
    qlogo->setScaledContents(true);
    qlogo->setFixedSize(0, 0);

    //----------------------------------------------------------- Main Layout -

    QGridLayout *layout = new QGridLayout;
    int row = 0;
    layout->addWidget(qlabl1, row, 0);
    layout->addWidget(nps_widg, row, 1);
    row = row + 1;
    layout->addWidget(sdr_labl, row, 0);
    layout->addWidget(sdr_widg, row, 1);
    row = row + 1;
    layout->addWidget(PE_labl, row, 0);
    layout->addWidget(PE_widg, row, 1);
    row = row +1;
    layout->setRowMinimumHeight(row, 25);

    row = row + 1;
    layout->addWidget(OD_labl, row, 0);
    layout->addWidget(OD_widg, row, 1, 1, 3);
    row = row + 1;
    layout->addWidget(ID_labl, row, 0);
    layout->addWidget(ID_widg, row, 1, 1, 3);
    row = row + 1;
    layout->addWidget(WT_labl, row, 0);
    layout->addWidget(WT_widg, row, 1, 1, 3);

    row = row +1;
    layout->setRowMinimumHeight(row, 25);
    row = row + 1;
    layout->addWidget(PR_labl, row, 0);
    layout->addWidget(PR_widg, row, 1, 1, 3);
    row = row + 1;
    layout->addWidget(BP_labl, row, 0);
    layout->addWidget(BP_widg, row, 1, 1, 3);

    row = row +1;
    layout->setRowMinimumHeight(row, 25);
    row = row +1;
    layout->addWidget(qlogo, row, 0, 1, 3);
    layout->addWidget(nps_info, row, 3);


    layout->setColumnStretch(5, 100);

    this->setLayout(layout);
    this->npsChanged();

connect(nps_widg, SIGNAL(currentIndexChanged(int)), this, SLOT (npsChanged()));
connect(sdr_widg, SIGNAL(valueChanged(double)), this, SLOT (npsChanged()));
connect(PE_widg, SIGNAL(currentIndexChanged(int)), this, SLOT (npsChanged()));
connect(nps_info, SIGNAL(clicked(bool)), this, SLOT (showInfo()));
}

void MainWindow::show()  // -------------------------------------------- Show -
{
 QFontMetrics fm(ID_widg->fontMetrics());
 int pxw = fm.boundingRect("(666.66 mm + 66.66 mm)").width() + 12;
 int pxh = fm.boundingRect("(666.66 mm)").height()*2 + 12;


 OD_widg->setFixedWidth(pxw);
 OD_widg->setFixedHeight(pxh);

 ID_widg->setFixedWidth(pxw);
 ID_widg->setFixedHeight(pxh);

 WT_widg->setFixedWidth(pxw);
 WT_widg->setFixedHeight(pxh);

 double h = 36;
 double w = h/163*1297;
 qlogo->setFixedHeight(h);
 qlogo->setFixedWidth(w);

 this->setFixedSize(this->minimumSizeHint());

 QRect qr = this->frameGeometry();
 QPoint cp = QDesktopWidget().availableGeometry().center();
 qr.moveCenter(cp);
 this->move(qr.topLeft());

 QWidget::show();
 qinfo->firstShow();
}

void MainWindow::showInfo()  // ----------------------------------- Show Info -
{
 qinfo->show();
}
void MainWindow::npsChanged()  // -------------------------------- npsChanged -
{
    QString pm = QString::fromUtf8(" ± ");
    QString t;

    int i = nps_widg->currentIndex();
    double od = OD[i];

    t = "<p align=center>" + QString::number(od, 'f', 3) + " in.";
    t += pm + QString::number(ODtol[i], 'f', 3) + " in.<br>";
    t += "(" + QString::number(od*25.4, 'f', 2) + " mm" + pm;
    t += QString::number(ODtol[i]*25.4, 'f', 2) + " mm)</p>";
    OD_widg->setText(t);

    double sdr = sdr_widg->value();
    double tmin = std::max(0.060, od / sdr);  // minimum wall thickness
    double ttol = std::max(0.02, tmin*0.12);  // tolerance
    double tmean = tmin + ttol/2;

    double id = std::max(0.0, od - (2.0*tmean));  // Inside diameter
    double idtol = ttol/2 + ODtol[i];

    t = "<p align=center>" + QString::number(id, 'f', 3) + " in.";
    t += pm + QString::number(idtol, 'f', 3) + " in.<br>";
    t += "(" + QString::number(id*25.4, 'f', 2) + " mm" + pm;
    t += QString::number(idtol*25.4, 'f', 2) + " mm)</p>";
    ID_widg->setText(t);

    t = "<p align=center>";
    if(tmin > 0.060)
    {
        t += QString::number(tmin, 'f', 3);
    }
    else
    {
        t += "<font color=red>" + QString::number(tmin, 'f', 3) + "</font>";
    }
    t += " in. + ";
    if(ttol > 0.02)
    {
        t += QString::number(ttol, 'f', 3);
    }
    else
    {
        t += "<font color=red>" + QString::number(ttol, 'f', 3) + "</font>";
    }
    t += " in.<br>(";
    t += QString::number(tmin*25.4, 'f', 2) + " mm + ";
    t += QString::number(ttol*25.4, 'f', 2) + " mm)</p>";
    WT_widg->setText(t);

    // Min. Burst Pressure

    i = PE_widg->currentIndex();

    double ats = ATS[i];  // Apparent Tensile Strength
    double BP = 2*ats / (sdr-1);
    t = QString::number(BP, 'f', 0) + " psi";
    t += " (" + QString::number(BP*0.00689476, 'f', 2) + " MPa)";
    BP_widg->setText(t);

    // Pressure Rating

    double hds23 = HDS23[i];  // Hydrostatic Design Stress
    double PR = 2*hds23 / (sdr-1);
    t = QString::number(PR, 'f', 0) + " psi";
    t += " (" + QString::number(PR*0.00689476, 'f', 2) + " MPa)";
    PR_widg->setText(t);

}
