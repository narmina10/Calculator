# Simple Calculator in Qt Creator
---

This project implements a simple calculator with basic arithmetic operations and additional functions like exponentiation, square root, sine, and cosine.

## Files
- Calc.pro<br>
  A configuration file used to manage project settings, dependencies, and build configurations.
- calculator.cpp<br>
  A c++ class Calculator which contains the functionality and some visual aspects of the calculator widget.
- calculator.h<br>
A header file of the class Calculator.
- main.cpp<br>
Main fuction that calls for the calculator widget.
___
## Code explanation
### In calculator.cpp:
```
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
```
These are header file inclusions for Qt classes used in the Calculator class.

```
class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget* parent = 0);

private slots:
    void slotButtonClicked();

private:
    QLabel* m_display;
    QString m_displayText;
    QPushButton* createButton(const QString& text);
    void calculate();
    QStringList m_stack;
};
```
- **Calculator Class:**<br> Inherits from QWidget, making it a widget that can be added to Qt applications.
- **Q_OBJECT Macro**:<br> Required for using Qt's meta-object system, enabling features like signals and slots.
- **Public Member Functions**:<br>
Calculator(QWidget* parent = 0): Constructor for the Calculator class. <br>
- **Private Slots:** <br>
**void slotButtonClicked()**: Slot function triggered when buttons are clicked.<br>
- **Private Members:** <br>
***QLabel* m_display**: Widget for displaying calculator input/output. <br>
**QString m_displayText**: Stores the text displayed on the calculator. <br>
***QPushButton* createButton(const QString& text)**: Utility function to create calculator buttons.<br>
**void calculate()**: Performs arithmetic calculations based on user input.<br>
**QStringList m_stack**: Stack to manage calculator operations.

```
Calculator::Calculator(QWidget* parent) : QWidget(parent) {
    m_display = new QLabel("0");
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMinimumSize(150, 50);

    const char buttons[4][4] = {
                                 {'7', '8', '9', ':'},
                                {'4', '5', '6', 'x'},
                                {'1', '2', '3', '-'},
                                {'0', '.', '=', '+'}};

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(m_display, 0, 0, 1, 4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QPushButton* button = createButton(QString(buttons[i][j]));
            layout->addWidget(button, i + 1, j);
        }
    }
```
In this part of the code I set a display for our calculator (a QLabel named m_display is created with an initial text of "0". Then it is aligned to the right (Qt::AlignRight) and set to a minimum size of 150x50 pixels.<br>

An array "buttons" is defined to hold characters for calculator buttons in a 4x4 grid format. <bt> 
Then I use a loop to create buttons.

```
  QPushButton* clearButton = createButton("CE");
    clearButton->setIcon(QIcon(":/cat.png"));
    clearButton->setIconSize(QSize(35, 35));
    layout->addWidget(clearButton, 0, 0, 1, 2);

    QPushButton* square = createButton("Хⁿ");
    layout->addWidget(square, 5, 0, 1, 1);

    QPushButton* squareroot = createButton("√");
    layout->addWidget(squareroot, 5, 1, 1, 1);

    QPushButton* sin = createButton("sin(x)");
    layout->addWidget(sin, 5, 2, 1, 1);

    QPushButton* cos = createButton("cos(x)");
    layout->addWidget(cos, 5, 3, 1, 1);
```
Here additional buttons sush as "CE", power, square root, sinus and cosinus operations are created and placed in layout.<br> 
```
QPushButton* Calculator::createButton(const QString& text) {
    QPushButton* button = new QPushButton(text);
    button->setStyleSheet("background-color: white");
    button->setMinimumSize(50, 50);
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return button;
}
```
This method creates and configures a QPushButton object with a specified text label, style, and minimum size. It also establishes a connection between the button's "clicked()" signal and a slot in the "Calculator" class for handling button clicks.
#### Calculate function

```
void Calculator::calculate() {
    double operand2 = m_stack.takeLast().toDouble();
    QString operation = m_stack.takeLast();
    double operand1 = m_stack.takeLast().toDouble();
    double result = 0;

    if (operation == "+") {
        result = operand1 + operand2;
    } else if (operation == "-") {
        result = operand1 - operand2;
    } else if (operation == ":") {
        result = operand1 / operand2;
    } else if (operation == "x") {
        result = operand1 * operand2;
    }
    else if (operation == "Хⁿ") {
        result = pow(operand1, operand2);
    }
    else if (operation == "√") {
        result = sqrt(operand1);
    }
    else if (operation == "sin(x)") {
        result = sin(operand1);
    }
    else if (operation == "cos(x)") {
        result = cos(operand1);
    }


    m_display->setText(QString::number(result));
}
```
Here, firstly, operands and a type of operation are extracted from the stack. Then specific mathematical actions are performed according to the type on the operation. At the end, the result is shown on calculator display. 

#### slotButtonClicked function

```
void Calculator::slotButtonClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QString text = clickedButton->text();

    if (text == "CE") {
        m_stack.clear();
        m_displayText = "";
        m_display->setText("0");
    } else if (text.at(0).isDigit()) {
        m_displayText += text;
        m_display->setText(m_displayText);
    } else if (text == ".") {
        if (!m_displayText.contains(".")) {
            m_displayText += text;
            m_display->setText(m_displayText);
        }
    } else {
        if (m_stack.size() >= 2) {
            m_stack.append(m_displayText);
            calculate();
            m_stack.clear();
            m_stack.append(m_displayText);
            if (text != "=") {
                m_stack.append(text);
            }
        } else {
            m_stack.append(m_displayText);
            m_stack.append(text);
            m_displayText = "";
            m_display->setText("0");
        }
    }
}
```
This method handles button clicks on the calculator interface, managing input, arithmetic operations, and display updates based on the clicked button's text. <br>

___

### In main.cpp:
```
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
```
An object of the class Calculator called "calculator" is created. Certain visual features such as font, background color, window icon and title are set. Also size of the window is defined. Then using "show()" the calculator Widget is opened. <br>

---
## How to use

1. Copy calculator.h, calculator.cpp, main.cpp files to respective directories of your project in Qt Creator.
2. Download png files for icons (or you could change them to whatever you want.
3. Run the program.


