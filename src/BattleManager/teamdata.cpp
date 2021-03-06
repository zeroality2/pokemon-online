#include "teamdata.h"

TeamData::TeamData(TeamBattle *team)
{
    if (!team) {
        for (int i = 0; i < 6; i++) {
            pokemons.push_back(new ShallowBattlePoke());
        }
    } else {
        for (int i = 0; i < 6; i++) {
            pokemons.push_back(new PokeBattle(team->poke(i)));
        }
    }
}

TeamData::~TeamData() {
    foreach(ShallowBattlePoke *poke, pokemons) {
        delete poke;
    }
}

ShallowBattlePoke* TeamData::poke(int slot)
{
    return pokemons[slot];
}

QString &TeamData::name()
{
    return mName;
}

void TeamData::setPoke(int slot, ShallowBattlePoke *poke)
{
    *pokemons[slot] = *poke;
}

void TeamData::setPoke(int slot, PokeBattle *poke)
{
    PokeBattle* trans = dynamic_cast<PokeBattle*>(pokemons[slot]);

    if (!trans)  {
        *pokemons[slot] = *poke;
    } else {
        *trans = *poke;
    }
}

void TeamData::setTeam(TeamBattle *team)
{
    for (int i = 0; i < 6; i++) {
        setPoke(i, &team->poke(i));
    }
}

void TeamData::switchPokemons(int slot1, int slot2)
{
    std::swap(pokemons[slot1],pokemons[slot2]);
}
