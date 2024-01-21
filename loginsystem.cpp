#include "loginsystem.h"
#include <QMessageBox>

LoginSystem::LoginSystem(QObject *parent)
    : QObject{parent}
{
    InitDB();
}

LoginSystem::~LoginSystem()
{
    if (db.isOpen())
        db.close();
}

void LoginSystem::performLogin(const QString &login, const QString &pass)
{
    QSqlQuery q;
    q.prepare("SELECT login, password FROM users WHERE login = :login AND password = :password");
    q.bindValue(":login", login);
    q.bindValue(":password", pass);

    if (!q.exec())
    {
        QString errText = q.lastError().text();
        showMessageBox(tr("Ошибка"),
                       errText);
        return;
    }

    if (q.next())
    {
        showMessageBox(tr("Успех"),
                       tr("Логин выполнен успешно!"));
    }
    else
    {
        showMessageBox(tr("Неудача"),
                       tr("Пользователя с данным логином или паролем не существует!"));
    }
}

void LoginSystem::performRegistration(const QString &login, const QString &pass)
{
    QSqlQuery q;
    q.prepare("INSERT INTO users (login, password) "
              "VALUES (:login, :password)");
    q.bindValue(":login", login);
    q.bindValue(":password", pass);

    if (!q.exec())
    {
        QSqlError err = q.lastError();

        if (err.type() == QSqlError::NoError)
        {
            showMessageBox(tr("Ошибка"),
                           tr("Произошла неизвестная ошибка."));
        }
        else
        {
            if (err.nativeErrorCode() == "23505")
            {
                showMessageBox(tr("Неудача"),
                               tr("Логин уже занят!"));
            }
            else
            {
                showMessageBox(tr("Ошибка"),
                               err.text());
            }
        }
    }
    else
    {
        showMessageBox(tr("Успех"),
                       tr("Регистрация выполнена успешно!"));
    }
}

bool LoginSystem::InitDB()
{
    QString hostname = "localhost";
    QString dbname = "login_system";
    QString username = "postgres";
    QString password = "123456";

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(hostname);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);

    try
    {
        bool ok = db.open();
        if (!ok)
            throw std::runtime_error("Failed to open database");
    }
    catch(const std::exception &e)
    {
        qDebug() << "Error: " << e.what();
        return false;
    }

    bool ok;
    QSqlQuery q;
    QString command = "SELECT * FROM users";
    ok = q.exec(command);
    if (ok)
        while(q.next())
            qDebug() << q.value(0).toString();

    return true;
}

void LoginSystem::showMessageBox(const QString &header, const QString &text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(header);
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    msgBox.exec();
}
