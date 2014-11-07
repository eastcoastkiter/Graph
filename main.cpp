#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QResource>
#include <QLocale>

#include "agraph.h"



int main( int argc, char ** argv ) {


    QApplication window( argc, argv );

    AGraph *mw = new AGraph();
    QIcon mwIcon(":/info.png");
        mw->setWindowIcon(mwIcon);
       // mw->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
       // mw->show();

    window.connect( &window, SIGNAL(lastWindowClosed()), &window, SLOT(quit()) );
    return window.exec();
}


