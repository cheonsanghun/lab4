#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);
    window.setWindowTitle("TextEdit Example");

    // QTextEdit 위젯 생성
    QTextEdit *textEdit1 = new QTextEdit(&window);
    QTextEdit *textEdit2 = new QTextEdit(&window);

    // QPushButton 위젯 생성
    QPushButton *button = new QPushButton("Click", &window);

    // QVBoxLayout을 사용하여 위젯 배치
    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(textEdit1);
    layout->addWidget(textEdit2);
    layout->addWidget(button);

    // 버튼 클릭 시그널과 람다 함수 연결
    QObject::connect(button, &QPushButton::clicked, [&]() {
        textEdit2->setText(textEdit1->toPlainText());
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}

