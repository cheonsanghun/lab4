#include <iostream>
#include "widget.h"
#include "ui_widget.h"
#include <QRegExp>
#include <QTcpSocket>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
    setWindowTitle("20171042 정규엽, 20183148 천상훈");
}
Widget::~Widget()
{
    delete ui;
    delete socket;
}
// 포트 연결 준비
void Widget::readyRead()
{
    while(socket->canReadLine())
    {
        QString line=QString::fromUtf8(socket->readLine());
        line=line.left(line.length()-1);
        ui->listWidget->addItem(QString("%2").arg(line));
    }
    ui->listWidget->scrollToBottom();
}

// 연결 시도
void Widget::connected()
{
    socket->write(QString("/me:"+ui->messageLineEdit->text()+"\n").toUtf8());  // 연결 시도
}
void Widget::on_connectButton_clicked()
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    socket->connectToHost(ui->ipLineEdit->text(),ui->portLineEdit->text().toInt());
}

// 보내기 버튼 콜백 메소드
void Widget::on_sendButton_clicked()
{
    QString message=ui->messageLineEdit->text().trimmed(); // 글자를 가져온다.
    if(!message.isEmpty()) // 메시지가 빈게 아니라면
    {
        socket->write(QString(message+"\n").toUtf8());
        // utf8 인코딩 타입으로 변환하여 소켓 전송
    }
    ui->messageLineEdit->clear();  // 전송 창 초기화
    ui->messageLineEdit->setFocus(); // 포커스 두기
}
void Widget::on_messageLineEdit_returnPressed()
{
    on_sendButton_clicked();
}

void Widget::on_openFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this); // 전송할 파일의 경로 저장
    ui->messageFilePath->setText(fileName); // 경로를 ui에 출력
}

void Widget::on_sendFile_clicked()
{
    if (fileName.isEmpty())
    {
        // 파일이 선택되지 않았을 경우
        qDebug() << "파일이 선택되지 않았습니다.";
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        // 파일을 열 수 없는 경우 오류
        qDebug() << "파일을 열 수 없습니다:" << file.errorString();
        return;
    }

    // 파일 내용 읽기
    QByteArray fileData = file.readAll();
    file.close();

    // 먼저 파일 크기를 전송
    QString fileSizeMessage = QString("/fileSize:%1\n").arg(fileData.size());
    socket->write(fileSizeMessage.toUtf8());
    socket->waitForBytesWritten(); // 크기 메시지가 전송될 때까지 대기

    // 실제 파일 데이터 전송
    socket->write(fileData);
    socket->waitForBytesWritten(); // 파일 데이터가 전송될 때까지 대기

    // 파일 전송 성공에 대한 알림 (선택 사항)
    qDebug() << "파일 전송이 성공적으로 완료되었습니다.";
}
