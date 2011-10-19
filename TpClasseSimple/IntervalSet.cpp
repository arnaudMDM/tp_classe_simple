/*************************************************************************
 IntervalSet  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par rgicquel
 *************************************************************************/

//---------- Réalisation de la classe <IntervalSet> (fichier IntervalSet.cpp) --
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "IntervalSet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void IntervalSet::Display ( )
// Algorithme : trivial
{
	IntervalSet * pInter = this;
	if ( Count ( ) > 0 )
	{
		do
		{
			cout << "[ " << pInter->borneInf << ", " << pInter->borneSup << " ]"
			        << endl;
			pInter = pInter->suivant;
		}
		while (pInter != 0);
	}
	cout << "Nombre d'intervalles : " << Count ( ) << endl;
} //----- Fin de Display

bool IntervalSet::Add ( long lLeft, long lRight )
// Algorithme :
{
	if ( lLeft > lRight )
	{
		return false;
	}

	if ( Count ( ) == 0 )
	{
		borneInf = lLeft;
		borneSup = lRight;
		nbInter++;
	}
	else if ( lRight < borneInf )
	{ // cas particulier : insertion avant le 1er élément
		IntervalSet * pInter = new IntervalSet ( *this );
		borneInf = lLeft;
		borneSup = lRight;
		suivant = pInter;
		nbInter++;
	}
	else
	{
		if ( !addRecursive ( lLeft, lRight ) )
		{
			return false;
		}
	}

	return true;
} //----- Fin de Add

bool IntervalSet::Add ( IntervalSet& is )
// Algorithme : trivial
{
	if ( is.Count ( ) == 0 )
	{
		return true;
	}

	IntervalSet * pInter = this;
	IntervalSet * pInterIs = &is;

	if ( Count ( ) > 0 )
	{
		while (pInter != 0 && pInterIs != 0)
		{
			if ( pInterIs->borneSup < pInter->borneInf )
			{
				pInterIs = pInterIs->suivant;
			}
			else if ( pInterIs->borneInf > pInter->borneSup )
			{
				pInter = pInter->suivant;
			}
			else
			{
				return false;
			}
		}
	}
	// si on sort de la boucle, cela signifie que l'ajout peut être réalisé

	pInterIs = &is;

	while (pInterIs != 0)
	{
		Add ( pInterIs->borneInf, pInterIs->borneSup );
		pInter = pInterIs->suivant;
	}

	return true;
} //----- Fin de Add

bool IntervalSet::Remove ( long lPos )
// Algorithme : Traitement des cas particuliers (argument invalide, 1er élément
//		de la liste ou liste d'un seul élément) puis cas général
{
	if ( lPos < 0 || lPos >= Count ( ) )
	{
		return false;
	}

	if ( Count ( ) == 1 )
	{
		nbInter--;
		return true;
	}

	if ( lPos == 0 )
	{
		borneInf = suivant->borneInf;
		borneSup = suivant->borneSup;
		Remove ( 1 );
		return true;
	}

	IntervalSet * pInter = this;
	// on souhaite se placer juste avant l'élément à supprimer
	for ( int i = 1; i < lPos; i++ )
	{
		pInter->nbInter--;
		pInter = pInter->suivant;
	}

	pInter->nbInter--;
	IntervalSet * pInterSuppr = pInter->suivant;

	pInter->suivant = pInter->suivant->suivant;
	pInterSuppr->suivant = 0; // on "casse" le lien pour éviter une suppression
	// en cascade lors de l'appel du destructeur

	delete pInterSuppr;

	return false;

} //----- Fin de Remove

long IntervalSet::Count ( ) const
// Algorithme : trivial
{
	return nbInter;
} //----- Fin de Count

bool IntervalSet::GetInterval ( long lPos, long& lLeft, long& lRight ) const
// Algorithme : trivial
{
	if ( lPos < 0 || lPos >= Count ( ) )
	{
		return false;
	}

	const IntervalSet * pInter = this;
	for ( int i = 0; i < lPos; i++ )
	{
		pInter = pInter->suivant;
	}

	lLeft = pInter->borneInf;
	lRight = pInter->borneSup;

	return true;
} //----- Fin de GetInterval

IntervalSet& IntervalSet::Union ( IntervalSet& is2 )
// Algorithme : trivial
{
	if ( Count ( ) == 0 )
	{
		return *(new IntervalSet ( *this ));
	}

	if ( is2.Count ( ) == 0 )
	{
		return *(new IntervalSet ( is2 ));
	}

	IntervalSet * pInter = this;
	IntervalSet * pInter2 = &is2;
	IntervalSet * pInterRetour = new IntervalSet ( );
	IntervalSet * pInterNew = pInterRetour;

	int borneInfNew, borneSupNew;
	int nbInterNew = 0;

	while (pInter != 0 && pInter2 != 0)
	{
		if ( pInter2->borneSup < pInter->borneInf )
		{
			pInterNew->suivant = new IntervalSet ( );
			pInterNew = pInterNew->suivant;
			pInterNew->borneInf = pInter2->borneInf;
			pInterNew->borneSup = pInter2->borneSup;
			nbInterNew++;

			pInter2 = pInter2->suivant;
		}
		else if ( pInter2->borneInf > pInter->borneSup )
		{
			pInterNew->suivant = new IntervalSet ( );
			pInterNew = pInterNew->suivant;
			pInterNew->borneInf = pInter->borneInf;
			pInterNew->borneSup = pInter->borneSup;
			nbInterNew++;

			pInter = pInter->suivant;
		}
		else
		{
			borneInfNew =
			        pInter->borneInf <= pInter2->borneInf ? pInter->borneInf :
			                pInter2->borneInf;

			bool finCroisement = false;

			while (pInter != 0 && pInter2 != 0 && !finCroisement)
			{
				if ( pInter2->borneSup < pInter->borneInf )
				{
					borneSupNew = pInter2->borneSup;
					pInter2 = pInter2->suivant;
					finCroisement = true;
				}
				else if ( pInter2->borneInf > pInter->borneSup )
				{
					borneSupNew = pInter->borneSup;
					pInter = pInter->suivant;
					finCroisement = true;
				}
				else if ( pInter2->borneSup >= pInter->borneSup )
				{
					pInter = pInter->suivant;
				}
				else
				{
					pInter2 = pInter2->suivant;
				}
			}

			if ( pInter == 0 && !finCroisement )
			{
				borneSupNew = pInter2->borneSup;
				pInter2 = pInter2->suivant;
			}
			else if ( pInter2 == 0 && !finCroisement )
			{
				borneSupNew = pInter->borneSup;
				pInter = pInter->suivant;
			}

			pInterNew->suivant = new IntervalSet ( );
			pInterNew = pInterNew->suivant;
			pInterNew->borneInf = borneInfNew;
			pInterNew->borneSup = borneSupNew;
			nbInterNew++;

		}
	}

	IntervalSet * pInter3 = 0;

	if ( pInter == 0 && pInter2 != 0 )
	{
		pInter3 = pInter2;
	}
	else if ( pInter != 0 && pInter2 == 0 )
	{
		pInter3 = pInter;
	}

	if ( pInter3 != 0 )
	{
		// on appelle le constructeur de copie car la fin de pInterNew sera
		// équivalente au reste de la liste d'intervalle non parcourue
		// entièrement
		pInterNew->suivant = new IntervalSet ( *pInter3 );
		nbInterNew += pInterNew->suivant->Count ( );
	}

	if ( pInterRetour->suivant != 0 )
	{
		pInter = pInterRetour;
		pInterRetour = pInterRetour->suivant;
		// on "casse" le lien pour éviter une destruction en cascade
		pInter->suivant = 0;
		delete (pInter);

		pInter = pInterRetour;
		while (pInter != 0)
		{
			pInter->nbInter = nbInterNew--;
			pInter = pInter->suivant;
		}
	}

	return *pInterRetour;
} //----- Fin de Union

IntervalSet& IntervalSet::Intersection ( IntervalSet& is2 )
// Algorithme : trivial
{
	if ( Count ( ) == 0 || is2.Count ( ) == 0 )
	{
		return *(new IntervalSet ( ));
	}

	IntervalSet * pInter = this;
	IntervalSet * pInter2 = &is2;
	IntervalSet * pInterRetour = new IntervalSet ( );
	IntervalSet * pInterNew = pInterRetour;

	int borneInfNew, borneSupNew;
	int nbInterNew = 0;

	while (pInter != 0 && pInter2 != 0)
	{
		if ( pInter2->borneSup < pInter->borneInf )
		{
			pInter2 = pInter2->suivant;
		}
		else if ( pInter2->borneInf > pInter->borneSup )
		{
			pInter = pInter->suivant;
		}
		else
		{
			borneInfNew =
			        pInter->borneInf >= pInter2->borneInf ? pInter->borneInf :
			                pInter2->borneInf;
			borneSupNew =
			        pInter->borneSup <= pInter2->borneSup ? pInter->borneSup :
			                pInter2->borneSup;

			pInterNew->suivant = new IntervalSet ( );
			pInterNew = pInterNew->suivant;
			pInterNew->borneInf = borneInfNew;
			pInterNew->borneSup = borneSupNew;
			nbInterNew++;

			if ( pInter2->borneSup >= pInter->borneSup )
			{
				pInter = pInter->suivant;
			}
			else
			{
				pInter2 = pInter2->suivant;
			}
		}
	}

	if ( pInterRetour->suivant != 0 )
	{
		pInter = pInterRetour;
		pInterRetour = pInterRetour->suivant;
		// on "casse" le lien pour éviter une destruction en cascade
		pInter->suivant = 0;
		delete (pInter);

		pInter = pInterRetour;
		while (pInter != 0)
		{
			pInter->nbInter = nbInterNew--;
			pInter = pInter->suivant;
		}
	}

	return *pInterRetour;
} //----- Fin de Intersection

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
IntervalSet::IntervalSet ( const IntervalSet & is )
// Algorithme : trivial
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <IntervalSet>" << endl;
#endif
	borneSup = is.borneSup;
	borneInf = is.borneInf;
	nbInter = is.nbInter;
	if ( is.suivant != 0 )
	{
		suivant = new IntervalSet ( *is.suivant );
	}
	else
	{
		suivant = 0;
	}
} //----- Fin de IntervalSet (constructeur de copie)

IntervalSet::IntervalSet ( ) :
		nbInter ( 0 ), suivant ( 0 )
// Algorithme : trivial
{
#ifdef MAP
	cout << "Appel au constructeur de <IntervalSet>" << endl;
#endif
} //----- Fin de IntervalSet

IntervalSet::~IntervalSet ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <IntervalSet>" << endl;
#endif

	delete suivant;
	// Attention, les objets seront supprimés en cascade au sein d'un intervalle
} //----- Fin de ~IntervalSet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool IntervalSet::addRecursive ( long lLeft, long lRight )
// Algorithme :
{
	if ( lLeft > borneSup )
	{
		if ( suivant == 0 || lRight < suivant->borneInf )
		{
			IntervalSet * pInterNew = new IntervalSet ( );
			pInterNew->Add ( lLeft, lRight );
			if ( suivant != 0 )
			{
				pInterNew->suivant = suivant;
			}
			suivant = pInterNew;

			nbInter++;
			return true;
		}
	}

	if ( suivant != 0 && suivant->addRecursive ( lLeft, lRight ) )
	{
		nbInter++;
		return true;
	}

	return false;
} //----- Fin de addRecursive

int IntervalSet::updateNbInter ( )
// Algorithme : récursif
{
	if ( suivant == 0 )
	{
		nbInter = 1;
		return 1;
	}

	nbInter = suivant->updateNbInter ( ) + 1;

	return nbInter;
} //----- Fin de updateNbInter
