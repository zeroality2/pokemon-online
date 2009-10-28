#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "../PokemonInfo/pokemoninfo.h"

class TB_Menu;
class TeamBuilder;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    TrainerTeam m_team;

    TB_Menu *m_menu;
    TeamBuilder *m_TB;

    TrainerTeam *trainerTeam();

public:
    MainWindow();

public slots:
    void launchMenu();
    void launchCredits();
    void launchTeamBuilder();
    void goOnline();
};

#endif // MAINWINDOW_H