#include <iostream>
#include <include/window/zwapp.h>
#include <qapplication.h>
#include <QFile>

int main(int argc, char** argv)
{
    ZwApp zweiExe(argc, argv);

    QFile file("../src/window/qresource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) 
    {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        zweiExe.setStyleSheet(styleSheet);
        file.close();
    }

    zweiExe.excute();
    return 0;
}