#include "pmwindow.h"
#include "../Utilities/otherwidgets.h"
#include "remove_direction_override.h"

PMWindow::PMWindow(int id, const QString &ownName, const QString &name, const QString &content, bool html)
    : m_ownName(ownName), escape_html(!html)
{
    setAttribute(Qt::WA_DeleteOnClose, true);

    this->id() = id;
    changeName(name);

    QGridLayout *l = new QGridLayout(this);
    this->setLayout(l);

    m_mainwindow = new QScrollDownTextBrowser();
    m_textToSend = new QIRCLineEdit();

    l->addWidget(m_mainwindow, 0,0,1,2);
    l->addWidget(m_textToSend, 1,0,1,2);

    m_challenge = new QPushButton(tr("&Challenge"));
    m_send = new QPushButton(tr("&Ignore"));
    m_send->setCheckable(true);

    l->addWidget(m_challenge,2,0);
    l->addWidget(m_send,2,1);

    printLine(content, false);

    connect(m_textToSend, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    connect(m_send, SIGNAL(toggled(bool)), this, SLOT(ignore(bool)));

    QSignalMapper *s = new QSignalMapper(this);
    s->setMapping(m_challenge, id);
    connect(m_challenge, SIGNAL(clicked()), s, SLOT(map()));
    connect(s, SIGNAL(mapped(int)), SIGNAL(challengeSent(int)));
}

void PMWindow::changeName(const QString &newname)
{
    this->m_name = newname;
    setWindowTitle(newname);
}

void PMWindow::changeSelf(const QString &newname)
{
    this->m_ownName = newname;
}

void PMWindow::printLine(QString line, bool self)
{
    if (line.trimmed().length() == 0)
        return;

    QSettings s;
    bool tt = s.value("show_timestamps2").toBool();
    QString timeStr = "";

    if (tt)
        timeStr += "(" + QTime::currentTime().toString("hh:mm") + ") ";

    if (escape_html) {
        line = escapeHtml(line);
    }

    if (self) {
        printHtml(toColor(timeStr + "<b>" + escapeHtml(m_ownName) + ": </b>", Qt::darkBlue) + line, false);
    } else {
        printHtml(toColor(timeStr + "<b>" + escapeHtml(name()) + ": </b>", Qt::darkGray) + line, false);
//        if (!QApplication::activeWindow()) {
//            QApplication::alert(this, 10000);
//            //raise();
//        }
    }
}

void PMWindow::printHtml(const QString &htmlCode, bool timestamps)
{
    QSettings s;
    bool tt = s.value("show_timestamps2").toBool();
    QString timeStr = "";

    if (tt && timestamps)
        timeStr += "(" + QTime::currentTime().toString("hh:mm") + ") ";

    m_mainwindow->insertHtml(timeStr + removeDirectionOverride(htmlCode) + "<br />");
}

void PMWindow::sendMessage()
{
    QString str = m_textToSend->text().trimmed();
    m_textToSend->clear();

    if (str.length() == 0) {
        return;
    }

    if (str.length() > 0) {
        QStringList s = str.split('\n');
        foreach(QString s1, s) {
            if (s1.length() > 0) {
                emit messageEntered(id(), s1);
                printLine(s1, true);
            }
        }
    }
}

void PMWindow::ignore(bool yes)
{
    emit ignore(id(), yes);
}

void PMWindow::disable()
{
    printHtml("<i>" + tr("The other party left the server, so the window was disabled.") + "</i>");
    blockSignals(true);
    m_challenge->setDisabled(true);
    m_send->setDisabled(true);
    m_textToSend->setDisabled(true);
}
