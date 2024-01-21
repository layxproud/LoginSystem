#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QObject>
#include <QtSql>
#include <QtDebug>

class LoginSystem : public QObject
{
    Q_OBJECT
public:
    explicit LoginSystem(QObject *parent = nullptr);
    ~LoginSystem();

    void performLogin(const QString &login, const QString &pass);
    void performRegistration(const QString &login, const QString &pass);

private:
    QSqlDatabase db;
    bool InitDB();

    void showMessageBox(const QString &header, const QString &text);
};

#endif // LOGINSYSTEM_H
