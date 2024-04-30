#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

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


    setLayout(layout);


}



QPushButton* Calculator::createButton(const QString& text) {
    QPushButton* button = new QPushButton(text);
    button->setStyleSheet("background-color: white");
    button->setMinimumSize(50, 50);
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return button;
}

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
