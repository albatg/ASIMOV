#include "main_asimov.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_asimov w;
    w.show();
    return a.exec();
}
