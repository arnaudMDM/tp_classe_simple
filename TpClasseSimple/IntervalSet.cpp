/*************************************************************************
 IntervalSet  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par Robin Gicquel et Arnaud Mery de Montigny
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
// Algorithme : Trivial
{
	if ( Count ( ) > 0 )
	{
		IntervalSet * pInter = this;
		while (pInter != 0)
		{
			cout << "[ " << pInter->borneInf << ", " << pInter->borneSup << " ]"
			        << endl;
			pInter = pInter->suivant;
		}
	}
	cout << "Nombre d'intervalles : " << Count ( ) << endl;
} //----- Fin de Display

bool IntervalSet::Add ( long lLeft, long lRight )
// Algorithme : Traitement des cas particuliers (arguments invalide, aucun
// élément dans l'ensemble, élément à insérer au début de la liste) puis cas
// général
{
	// cas où les arguments invalides
	if ( lLeft > lRight )
	{
		return false;
	}

	// cas où l'ensemble de départ vide
	if ( Count ( ) == 0 )
	{
		borneInf = lLeft;
		borneSup = lRight;
		nbInter = 1;

		return true;
	}

	// cas ou l'élément doit être inséré en début de liste
	if ( lRight < borneInf )
	{
		IntervalSet * pInterNew = new IntervalSet ( );

		pInterNew->borneInf = borneInf;
		pInterNew->borneSup = borneSup;
		pInterNew->nbInter = nbInter;
		pInterNew->suivant = suivant;

		borneInf = lLeft;
		borneSup = lRight;
		suivant = pInterNew;
		nbInter++;

		return true;
	}

	// cas général
	IntervalSet * pInter = this;
	int nbInterNew = 2;

	while (pInter != 0)
	{
		if ( lLeft > pInter->borneSup )
		{
			if ( pInter->suivant == 0 || lRight < pInter->suivant->borneInf )
			{
				/*
				 Si on trouve l'endroit où insérer le nouvel intervalle, on
				 procède de cette manière : on crée dynamiquement un nouvel
				 intervalle qui va venir remplacer le "suivant" de
				 l'intervalle précédant le point d'insertion. En tant que
				 "suivant" du nouvel intervalle, on choisit l'intervalle qui
				 suit le point d'insertion (de cette manière, si l'intervalle
				 est ajouté en fin de liste, un 0 sera affecté au pointeur
				 sans opération spécifique).
				 */

				IntervalSet * pInterNew = new IntervalSet ( );

				pInterNew->borneInf = lLeft;
				pInterNew->borneSup = lRight;
				pInterNew->nbInter = pInter->nbInter;
				pInterNew->suivant = pInter->suivant;

				pInter->suivant = pInterNew;

				// On parcourt à nouveau la liste jusqu'à l'ensemble ajouté pour
				// mettre à jour le nombre d'éléments de chaque IntervalSet de
				// la liste
				IntervalSet * pInter2 = this;
				while (pInter2 != pInterNew)
				{
					pInter2->nbInter = nbInterNew;
					nbInterNew--;
					pInter2 = pInter2->suivant;
				}

				return true;
			}
			else
			{
				nbInterNew++;
			}
		}
		else
		{
			return false;
		}

		pInter = pInter->suivant;
	}

	return false;
} //----- Fin de Add

bool IntervalSet::Add ( IntervalSet& is2 )
// Algorithme : Les ajouts ne doivent être effectués que s'ils sont tous
// possibles. Après avoir testé que l'IntervalSet passé en paramètre n'est
// pas vide, on parcourt les deux intervalSet en même temps pour savoir s'il y
// a collision à un moment ou un autre entre deux intervalles.
{
	if ( is2.Count ( ) == 0 )
	{
		return true;
	}

	IntervalSet * pInter = this;
	IntervalSet * pInter2 = &is2;

	if ( Count ( ) > 0 )
	{
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
			// si aucune des deux conditions précédentes n'est validée, c'est
			// qu'il y a collision et que l'ajout ne pourra pas se faire; on
			// sort donc immédiatement de la fonction
			else
			{
				return false;
			}
		}
	}

	// si on sort de la boucle, cela signifie que l'ajout peut être réalisé

	pInter2 = &is2;

	while (pInter2 != 0)
	{
		Add ( pInter2->borneInf, pInter2->borneSup );
		pInter2 = pInter2->suivant;
	}

	return true;
} //----- Fin de Add

bool IntervalSet::Remove ( long lPos )
// Algorithme : Traitement des cas particuliers (argument invalide, liste de 0
// ou 1 intervalle ou liste d'un seul élément) puis cas général
{
	// cas où lPos est invalide et où la liste est vide
	if ( lPos < 0 || lPos >= Count ( ) )
	{
		return false;
	}

	// cas où la liste ne contient qu'un seul intervalle
	if ( Count ( ) == 1 )
	{
		nbInter--;
		return true;
	}

	// cas où on souhaite supprimer le premier intervalle de la liste
	if ( lPos == 0 )
	{
		// on recopie le deuxième élément dans le premier puis on supprime le
		// deuxième
		borneInf = suivant->borneInf;
		borneSup = suivant->borneSup;
		Remove ( 1 );
		return true;
	}

	IntervalSet * pInter = this;
	// on souhaite se placer juste avant l'élément à supprimer, on en profite
	// pour mettre à jour le nombre d'élements des intervalSet précédant celui
	// que l'on souhaite supprimer
	for ( int i = 1; i < lPos; i++ )
	{
		pInter->nbInter--;
		pInter = pInter->suivant;
	}

	pInter->nbInter--;
	IntervalSet * pInterSuppr = pInter->suivant;

	pInter->suivant = pInter->suivant->suivant;

	// on "casse" le lien pour éviter une suppression en cascade lors de
	// l'appel du destructeur
	pInterSuppr->suivant = 0;

	delete pInterSuppr;

	return false;

} //----- Fin de Remove

long IntervalSet::Count ( ) const
// Algorithme : trivial
{
	return nbInter;
} //----- Fin de Count

bool IntervalSet::GetInterval ( long lPos, long& lLeft, long& lRight ) const
// Algorithme : Test de la validité des arguments puis parcourt jusqu'à
// l'intervalle voulu
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
// Algorithme : Traitement des cas particuliers (aucun intervalle dans un des
// ensembles) puis cas général
{
	if ( Count ( ) == 0 )
	{
		return *(new IntervalSet ( is2 ));
	}

	if ( is2.Count ( ) == 0 )
	{
		return *(new IntervalSet ( *this ));
	}

	IntervalSet * pInter = this;
	IntervalSet * pInter2 = &is2;
	// on initialise la liste de retour avec un IntervalSet vide de manière à
	// disposer dès le début de pInterNew->suivant et ainsi éviter le traitement
	// dans le cas général du cas particulier où la liste de retour est encore
	// vide
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
				else if ( pInter2->borneSup > pInter->borneSup )
				{
					pInter = pInter->suivant;
				}
				else if ( pInter2->borneSup < pInter->borneSup )
				{
					pInter2 = pInter2->suivant;
				}
				else
				{
					borneSupNew = pInter->borneSup;
					pInter = pInter->suivant;
					pInter2 = pInter2->suivant;
					finCroisement = true;
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
// Algorithme : Traitement des cas particuliers (aucun intervalle dans un
//ensemble ou dans les deux )puis cas général.
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
	//Cas général
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
// Algorithme :trivial
//
{
#ifdef MAP
	cout << "Appel au destructeur de <IntervalSet>" << endl;
#endif

	while (suivant != 0)
	{
		Remove ( 1 );
	}
} //----- Fin de ~IntervalSet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
