#ifndef SQLCONFIG_H
#define SQLCONFIG_H

#include <QtGui>

class SQLConfigWindow : public QWidget
{
    Q_OBJECT
public:
    SQLConfigWindow();

public slots:
    void apply();
    void changeEnabled();
    void exportDatabase();
private:
    QComboBox *b;
    QLineEdit *host, *name, *user, *pass, *schema;
    QSpinBox *port;
    QCheckBox *doVacuum;
};

#endif // SQLCONFIG_H
