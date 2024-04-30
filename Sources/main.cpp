#include <QApplication>
#include "Calculator.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Calculator   calculator;

    QFont font("Helvetica");
    font.setStyleHint(QFont::Cursive);
    QApplication::setFont(font);

    calculator.setStyleSheet("background-color: pink;");
    calculator.setWindowIcon(QIcon(":/cute.png"));
    calculator.setWindowTitle("Calculator");
    calculator.resize(270, 300);

    calculator.show();

    return app.exec();
}

