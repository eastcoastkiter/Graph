#ifndef AGRAPH_H
#define AGRAPH_H

#include <qcoreapplication.h>
#include <QThread>
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QFontDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QRegExp>
#include <QStatusBar>
#include <QString>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QProcess>
#include <QClipboard>
#include <QPixmap>
#include <QColor>
#include <QBitmap>
#include <QTextEdit>
#include <QMimeData>
#include <QToolButton>
#include <QIODevice>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <QSplitter>
#include <QStyle>
#include <QRectF>
#include <QPointF>

#include "readCom.h"
#include "graphView.h"
#include "graphScene.h"

#include "graphValue.h"

class AGraph: public QMainWindow
{
    Q_OBJECT

public:
    AGraph();
    ~AGraph(){}

private:
    QWidget* window;
    QPushButton* startButton;
    QPushButton* stopButton;
    QTextEdit* te;
    QThread workerThread;
    GraphView* gView;
    GraphScene* gScene;

    int counter;
    QCheckBox* autoScaleCheckBox;

    ReadCom* rc;
    bool threadIsStarted;
    QSpinBox * dotSizeSpinBox;
    QSpinBox * xTranslateSpinBox;
    QComboBox* portComboBox;
    QComboBox* baudRateComboBox;
    bool protectScene;
protected:

private slots:
    void about();
    void startThread();
    void stopThread();
    void clearView();
    void gSceneRectChanged(const QRectF &);
public slots:
    void handleComs(const QString &);
signals:
    void operate();
};
#endif
/* TODO
  if installPath not exists, then create
*/


