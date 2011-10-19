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
#include <cstdlib>
#include <ctime>

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

//	inter1.Add ( -18, -14 );
//	inter1.Add ( -5, 2 );
//	inter1.Add ( 3, 3 );
//	inter1.Add ( 8, 9 );
//	inter1.Add ( 10, 14 );
//
//	inter2.Add ( -13, -9 );
//	inter2.Add ( -3, 4 );
//	inter2.Add ( 5, 11 );
//	inter2.Add ( 15, 17 );
//
//	IntervalSet inter3 = inter1.Intersection ( inter2 );

//	inter1.Add ( -6, -4);
//	inter1.Add ( -2, 3);
//	inter1.Add ( 7, 8 );
//	inter1.Add ( 12, 18 );
//	inter1.Add ( 23, 28 );
//	inter1.Add ( 58, 63 );
//
//	inter2.Add ( 0, 1 );
//	inter2.Add ( 5, 20 );
//	inter2.Add ( 27, 45 );
//	inter2.Add ( 48, 52 );
//	inter2.Add ( 55, 60 );
//
//	IntervalSet inter3 = inter1.Intersection(inter2);
//
//	inter3.Display();

	int val, val2;
	time_t debut, fin;

	srand ( time ( NULL ) );

	for ( int i = 1; i <= 100000; i++ )
	{
		val = (rand()/((RAND_MAX+1)/2.0)-1)*RAND_MAX*100;
		val2 = (rand()/((RAND_MAX+1)/2.0)-1)*RAND_MAX*100;
		inter1.Add ( val >= val2 ? val2 : val, val >= val2 ? val : val2 );

		val = (rand()/((RAND_MAX+1)/2.0)-1)*RAND_MAX*100;
		val2 = (rand()/((RAND_MAX+1)/2.0)-1)*RAND_MAX*100;
		inter2.Add ( val >= val2 ? val2 : val, val >= val2 ? val : val2 );

		//cout << "Itération n° : " << i << endl;
	}

	cout << "Nb d'éléments de inter1 : " << inter1.Count ( ) << endl;
	cout << "Nb d'éléments de inter2 : " << inter2.Count ( ) << endl;

	debut = time ( NULL );
	IntervalSet inter3 = inter1.Union ( inter2 );
	fin = time ( NULL );

	cout << "Nb d'élements de inter3 : " << inter3.Count ( ) << endl;

	cout << "Temps d'exécution de l'union : " << difftime ( fin, debut )
	        << " secondes" << endl;

	debut = time ( NULL );
	IntervalSet inter4 = inter1.Intersection ( inter2 );
	fin = time ( NULL );

	cout << "Nb d'élements de inter4 : " << inter4.Count ( ) << endl;

	cout << "Temps d'exécution de l'intersection : " << difftime ( fin, debut )
	        << " secondes" << endl;

	return 1;

} //----- fin de main
