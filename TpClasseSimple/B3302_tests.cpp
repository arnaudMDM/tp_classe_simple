/*************************************************************************
 B3302_tests  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par rgicquel
 *************************************************************************/

//---------- Réalisation du module <B3302_tests> (fichier B3302_tests.cpp) -----
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "IntervalSet.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques

int main ( )
// Algorithme : trivial
{
	IntervalSet inter1;
	IntervalSet inter2;

	inter1.Add ( -18, -14 );
	inter1.Add ( -5, 2 );
	inter1.Add ( 3, 7 );
	inter1.Add ( 8, 9 );
	inter1.Add ( 10, 14 );

	inter2.Add ( -13, -9 );
	inter2.Add ( -3, 4 );
	inter2.Add ( 5, 11 );
	inter2.Add ( 15, 17 );

	IntervalSet inter3 = inter1.Union(inter2);

	inter3.Display ( );

	return 1;

} //----- fin de main
