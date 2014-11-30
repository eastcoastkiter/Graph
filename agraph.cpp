#include "agraph.h"
using namespace std;

AGraph::AGraph()
	: QMainWindow( 0 )
{
    threadIsStarted=false;
    counter=0;
    protectScene=false;

//main widget
window = new QWidget(this);

        setCentralWidget(window);
        resize(800,600);
        statusBar()->showMessage( tr("Welcome") );

        QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

        fileMenu->addSeparator ();

        QAction* exitAction   = new QAction(tr("&Exit"), window);
            exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
            connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
            fileMenu->addAction(exitAction);



            //setContentsMargins(0,0,0,0);
            //layout()->setContentsMargins(0,0,0,0);

        QGridLayout* ml = new QGridLayout(window);

        QSplitter *splitter = new QSplitter(window);
            splitter->setOrientation(Qt::Vertical);
            splitter->setHandleWidth(10);
            //splitter->setStyleSheet("QSplitter  { border-color: black; color: red;  height: 5px;background-color: green; }");
            //splitter->setFrameShape(QFrame::Box);
        ml->addWidget(splitter,0,0);


        QWidget* topWidget = new QWidget(this);
                splitter->addWidget(topWidget);
                topWidget->setContentsMargins(0,0,0,0);
                ml->setContentsMargins(0,0,0,0);

        QGridLayout *mainGrid = new QGridLayout (topWidget);

        QHBoxLayout * buttonBox = new QHBoxLayout();

        startButton = new QPushButton("start", this);
            buttonBox->addWidget(startButton);
        connect(startButton, SIGNAL(pressed()), this, SLOT(startThread()));

        stopButton = new QPushButton("stop", this);
            buttonBox->addWidget(stopButton);
        connect(stopButton,  SIGNAL(pressed()), this, SLOT(stopThread()));

        QPushButton* clearButton = new QPushButton("Clear", this);
            buttonBox->addWidget(clearButton);
        connect(clearButton,  SIGNAL(pressed()), this, SLOT(clearView()));

        mainGrid->addLayout(buttonBox,0,0);

      //  planeItem = new PlaneItem(this);
    //    mainGrid->addWidget(planeItem,1,0);

        gScene = new GraphScene(this);
        connect(gScene, SIGNAL(sceneRectChanged(const QRectF &)),this, SLOT(gSceneRectChanged(const QRectF &)));

        gView = new GraphView(gScene);
        gView->setScene(gScene);
        mainGrid->addWidget(gView,1,0);


        QGridLayout *optionsGrid = new QGridLayout (0);
            mainGrid->addLayout(optionsGrid,2,0);

/*        optionsGrid->addWidget(new QLabel("Port:"),0,0);
        portComboBox = new QComboBox(this);
            QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts();
            QStringList portListNames;
                for (int i = 0; i < portList.size(); ++i)
                {
                    portListNames << portList.at(i).portName();
                }
                portListNames.sort();
            portComboBox->insertItems(0, portListNames);
            portComboBox->setCurrentIndex(portComboBox->count()-1);
        optionsGrid->addWidget(portComboBox,0,1);

        QStringList baudRateListNames;
        baudRateComboBox = new QComboBox(this);
        QList<qint32> baudRateList = QSerialPortInfo::standardBaudRates();
        for (int i = 0; i < baudRateList.size(); ++i)
        {
            baudRateListNames << QString::number(baudRateList.at(i));
        }
        baudRateComboBox->insertItems(0,baudRateListNames);
        optionsGrid->addWidget(baudRateComboBox,0,2);
        baudRateComboBox->setCurrentText("9600");
*/
        optionsGrid->addWidget(new QLabel("Autoscale:"),1,0);

        autoScaleCheckBox = new QCheckBox(this);
            autoScaleCheckBox->setChecked(false);
        optionsGrid->addWidget(autoScaleCheckBox,1,1);

        optionsGrid->addWidget(new QLabel("Dot Size:"),2,0);
        dotSizeSpinBox = new QSpinBox(this);
            dotSizeSpinBox->setMinimum(1);
            dotSizeSpinBox->setMaximum(100);
            dotSizeSpinBox->setValue(3);
        optionsGrid->addWidget(dotSizeSpinBox,2,1);
        //connect(dotSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(clearView()));

        optionsGrid->addWidget(new QLabel("X Translate:"),3,0);
        xTranslateSpinBox = new QSpinBox(this);
            xTranslateSpinBox->setMinimum(1);
            xTranslateSpinBox->setMaximum(100);
            xTranslateSpinBox->setValue(10);
        optionsGrid->addWidget(xTranslateSpinBox,3,1);
        //connect(xTranslateSpinBox, SIGNAL(valueChanged(int)), this, SLOT(clearView()));

        optionsGrid->addItem(new QSpacerItem ( 0, 1, QSizePolicy::Expanding, QSizePolicy::Fixed ),1,3);
        mainGrid->addItem(new QSpacerItem ( 0, 600, QSizePolicy::Fixed, QSizePolicy::Expanding ),1,3);


        QWidget* buttomWidget = new QWidget(window);
                splitter->addWidget(buttomWidget);

        QVBoxLayout* teBox = new QVBoxLayout(buttomWidget);

            buttomWidget->setContentsMargins(0,0,0,0);
            buttomWidget->layout()->setContentsMargins(0,0,0,0);

          QFrame *line = new QFrame(buttomWidget);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setContentsMargins(0,0,0,0);
        teBox->addWidget(line);


        te = new QTextEdit(this);
            teBox->addWidget(te);



            // gKey->moveBy(counter,1);

            gView->show();
    show();



    //port->setPortName("com8");
}

void AGraph::handleComs(const QString &text)
{
    if (protectScene)
            return;

    int foundVal=0;

    te->append(text.trimmed());
    double x = 0.0;

    QStringList list = text.trimmed().split(QRegExp("\\n+"));

    for (int t=0; t<list.size(); ++t)
    {
        int index=list.at(t).trimmed().indexOf(QRegExp("x:|y:|z:"));

        if (index>-1)
        {
            QString tx=list.at(t).trimmed().section(":",1);
          //  qDebug() << "tx" << tx;
            x=tx.toDouble();
            QColor c;


            if (list.at(t).contains("x:"))
            {
                c=QColor(Qt::green);
                foundVal=1;
            }
            if (list.at(t).contains("y:"))
            {
                c=QColor(Qt::blue);
                foundVal=1;
            }
            if (list.at(t).contains("z:"))
            {
                c=QColor(Qt::red);
                foundVal=1;
            }
            if (list.at(t).contains("qx:"))
            {
                c=QColor(Qt::yellow);
                foundVal=1;
            }
            if (list.at(t).contains("qy:"))
            {
                c=QColor(Qt::lightGray);
                foundVal=1;
            }
            if (list.at(t).contains("qz:"))
            {
                c=QColor(Qt::cyan);
                foundVal=1;
            }

            if (foundVal==1)
            {
                GraphValue *gValue = new GraphValue(c,0);
                     gScene->addItem(gValue);
                     gValue->setScale(dotSizeSpinBox->value());
                     gValue->moveBy(counter*xTranslateSpinBox->value(),x*-10);
            }
            foundVal=0;
            gView->update();
        }

    }

    //qDebug() << t;




         if (autoScaleCheckBox->isChecked())
         {
            gView->autoScale();
         }
         else
         {
             gView->update();
         }
         gView->autoScroll();
    counter++;

}

void AGraph::startThread()
{
    if (threadIsStarted)
    {
        QMessageBox::warning(this, "Graph","Thread already running.");
        return;
    }


    rc = new ReadCom("portComboBox->currentText()",9600);
    rc->moveToThread(&workerThread);
    connect(this, SIGNAL(operate()), rc, SLOT(startCom()));
    connect(rc, SIGNAL(resultReady(const QString &)), this, SLOT(handleComs(const QString &)));
    workerThread.start();
    operate();
    threadIsStarted=true;
}

void AGraph::stopThread()
{
    if (!threadIsStarted)
        return;

    rc->close();
    QCoreApplication::processEvents();
    rc->deleteLater();

    //workerThread.terminate();
    threadIsStarted=false;
}

void AGraph::clearView()
{
    qDebug() << "clearView";
    stopThread();
     gScene->clear();
     gView->createGKey();

     counter=0;
     //gView->ensureVisible(0,0,gView->width(),gView->height(),50,50);
     gView->scene()->setSceneRect((gView->width()/2)*-1 ,(gView->height()/2)*-1,gView->width(),gView->height());
    // gView->ensureVisible(QRectF(0,0,gView->width(),gView->height()));

    gScene->update();

    /*
    protectScene=true;
        gScene->clear();
        counter=0;
    protectScene=false;
    */
}

void AGraph::gSceneRectChanged(const QRectF & rect)
{
    (void) rect;
   // qDebug() << "Slider" << rect;
}

void AGraph::about()
{
    QMessageBox::information(this, "Info", "written by Rene Storm (2014)\nLicense GPL v3\n\nVersion: 1.2\n\nhttps://github.com/eastcoastkiter/\n");
}

