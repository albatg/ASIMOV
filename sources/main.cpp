#include "main_asimov.h"

#include <QApplication>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QFile styleSheetFile("/Users/lgome/OneDrive/Escritorio/ASIMOV/Diffnes.qss");

    QFile styleSheetFile(":/Diffnes.qss");

    if (styleSheetFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        a.setStyleSheet(styleSheet);
    } else {

        qDebug() << "Error al abrir la hoja de estilos.";
    }
    main_asimov w;
    w.show();
    return a.exec();
}
