#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->setDocumentMode(true);
    ui->tabWidget->tabBar()->setExpanding(true);

    ui->loginInput_L->setMaxLength(20);
    ui->loginInput_R->setMaxLength(20);
    ui->passwordInput_L->setMaxLength(20);
    ui->passwordInput_R->setMaxLength(20);
    ui->repeatPasswordInput_R->setMaxLength(20);

    loginSystem = new LoginSystem(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);
}

MainWindow::~MainWindow()
{
    delete loginSystem;
    delete ui;
}

void MainWindow::onLoginButtonClicked()
{
    QString login = ui->loginInput_L->text();
    QString password = ui->passwordInput_L->text();

    if (login.isEmpty() || password.isEmpty())
        return;

    loginSystem->performLogin(login, password);
}

void MainWindow::onRegisterButtonClicked()
{
    QString login = ui->loginInput_R->text();
    QString password = ui->passwordInput_R->text();
    QString passwordRepeat = ui->repeatPasswordInput_R->text();

    if (login.isEmpty() || password.isEmpty() || passwordRepeat.isEmpty())
        return;

    if (password != passwordRepeat)
    {
        QMessageBox::critical(this,
                              tr("Ошибка"),
                              tr("Пароли не совпадают!"));
        return;
    }

    loginSystem->performRegistration(login, password);
}

