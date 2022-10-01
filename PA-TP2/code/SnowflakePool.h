#pragma once

#include <cstddef> // pour size_t
#include <memory> // pour unique_ptr
#include <iostream>

#include "Constants.h"
#include "Snowflake.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeRebound.h"
#include "SnowflakeSine.h"

using std::unique_ptr;
using std::make_unique;

template<typename T>
class SnowflakePool							//16 bytes
{
public:

	SnowflakePool() : nbParticles{0}
	{
		// Initialiser le pool d'objets
		pool = make_unique<T[]>(MAX_SNOWFLAKES);
	}

	void spawn()
	{
		// "Créer" un snowflake de plus en activant
		// le prochain snowflake inactif
		if(nbParticles <= MAX_SNOWFLAKES) ++nbParticles;
	}

	void destroy(size_t deleteIdx)
	{
		// "Supprimer" le snowflake demandé en déplaçant
		// le dernier snowflake utilisé par-dessus l'objet
		// à supprimer
		pool[deleteIdx] = pool[nbParticles];
		pool[nbParticles].init(rand() / (double)RAND_MAX * SCREEN_WIDTH);
	}

	T& get(size_t idx)
	{
		// Accès à un des snowflakes
		return pool[idx];
	}

	size_t getNbSnowflakes() const
	{
		return nbParticles;
	}

private:
	unique_ptr<T[]>	pool;		//8 bytes
	size_t nbParticles;			//8 bytes
};
