/*************************************************************************
 B3302_tests  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par Robin Gicquel et Arnaud Mery de Montigny
 *************************************************************************/

//---------- Réalisation du module <B3302_tests> (fichier B3302_tests.cpp) -----
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>


//------------------------------------------------------ Include personnel
#include "B3302_class.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques

int main ( )
// Algorithme : réalisation des tests tels qu'ils sont décrits dans les
// spécifications de IntervalSet
{
	int nTest;

	IntervalSet inter1;
	IntervalSet inter2;
	IntervalSet inter3;

	//test 101
	nTest = 101;

	inter1 = IntervalSet ( );

	if ( inter1.Count ( ) == 0 )
	{
		cout << "Test " << nTest << " : OK" << endl;
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 102
	nTest = 102;

	inter1 = IntervalSet ( );

	for ( int i = 1; i <= 10000; i++ )
	{
		inter1.Add ( (i * 10), (i * 10 + 1) );
	}
	if ( inter1.Count ( ) == 10000 )
	{
		cout << "Test " << nTest << " : OK" << endl;
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 201
	nTest = 201;

	inter1 = IntervalSet ( );
	inter2 = IntervalSet ( );

	inter3 = inter1.Union ( inter2 );

	if ( inter3.Count ( ) == 0 )
	{
		cout << "Test " << nTest << " : OK" << endl;
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 202
	nTest = 202;

	inter1 = IntervalSet ( );
	inter2 = IntervalSet ( );

	for ( int i = 1; i <= 30; i++ )
	{
		inter2.Add ( i * 10, i * 11 );
	}

	inter3 = inter1.Union ( inter2 );

	if ( inter2.Count ( ) == inter3.Count ( ) )
	{
		int nbInter = inter2.Count ( );

		long borneInf1;
		long borneInf2;
		long borneSup1;
		long borneSup2;

		bool erreur = false;

		for ( long i = 0; i < nbInter && !erreur; i++ )
		{
			inter3.GetInterval ( i, borneInf1, borneSup1 );
			inter2.GetInterval ( i, borneInf2, borneSup2 );

			if ( borneInf1 != borneInf2 || borneSup1 != borneSup2 )
			{
				cout << "Test " << nTest << " : Erreur" << endl;
				erreur = true;
			}
		}

		if ( !erreur )
		{
			cout << "Test " << nTest << " : OK" << endl;
		}
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 203
	nTest = 203;

	inter1 = IntervalSet ( );
	inter2 = IntervalSet ( );

	for ( int i = 1; i <= 30; i++ )
	{
		inter1.Add ( i * 10, i * 10 + 5 );
	}

	inter3 = inter1.Union ( inter2 );

	if ( inter1.Count ( ) == inter3.Count ( ) )
	{
		int nbInter = inter1.Count ( );

		long borneInf1;
		long borneInf2;
		long borneSup1;
		long borneSup2;

		bool erreur = false;

		for ( long i = 0; i < nbInter && !erreur; i++ )
		{
			inter3.GetInterval ( i, borneInf1, borneSup1 );
			inter1.GetInterval ( i, borneInf2, borneSup2 );

			if ( borneInf1 != borneInf2 || borneSup1 != borneSup2 )
			{
				cout << "Test " << nTest << " : Erreur" << endl;
				erreur = true;
			}

		}

		if ( !erreur )
		{
			cout << "Test " << nTest << " : OK" << endl;
		}
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 204
	nTest = 204;

	inter1 = IntervalSet ( );

	for ( int i = 1; i <= 2; i++ )
	{
		inter1.Add ( i * 10, i * 11 );
	}

	inter2 = inter1;

	inter3 = inter1.Union ( inter2 );

	if ( inter1.Count ( ) == inter3.Count ( ) )
	{

		int nbInter = inter1.Count ( );

		long borneInf1;
		long borneInf2;
		long borneSup1;
		long borneSup2;

		bool erreur = false;

		for ( long i = 0; i < nbInter && !erreur; i++ )
		{

			inter1.GetInterval ( i, borneInf1, borneSup1 );
			inter3.GetInterval ( i, borneInf2, borneSup2 );

			if ( borneInf1 != borneInf2 || borneSup1 != borneSup2 )
			{
				cout << "Test " << nTest << " : Erreur" << endl;
				erreur = true;
			}

		}

		if ( !erreur )
		{
			cout << "Test " << nTest << " : OK" << endl;
		}
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	//test 205
	nTest = 205;

	inter1 = IntervalSet ( );
	inter2 = IntervalSet ( );

	inter1.Add ( -6, -4 );
	inter1.Add ( -2, 3 );
	inter1.Add ( 7, 8 );
	inter1.Add ( 12, 18 );
	inter1.Add ( 23, 28 );
	inter1.Add ( 58, 63 );
	inter1.Add ( 70, 80 );
	inter1.Add ( 82, 92 );

	inter2.Add ( 0, 1 );
	inter2.Add ( 5, 20 );
	inter2.Add ( 27, 45 );
	inter2.Add ( 48, 52 );
	inter2.Add ( 55, 60 );
	inter2.Add ( 70, 80 );
	inter2.Add ( 92, 100 );

	inter3 = inter1.Union ( inter2 );

	inter1 = IntervalSet ( );

	inter1.Add ( -6, -4 );
	inter1.Add ( -2, 3 );
	inter1.Add ( 5, 20 );
	inter1.Add ( 23, 45 );
	inter1.Add ( 48, 52 );
	inter1.Add ( 55, 63 );
	inter1.Add ( 70, 80 );
	inter1.Add ( 82, 100 );

	if ( inter1.Count ( ) == inter3.Count ( ) )
	{

		int nbInter = inter1.Count ( );

		long borneInf1;
		long borneInf2;
		long borneSup1;
		long borneSup2;

		bool erreur = false;

		for ( long i = 0; i < nbInter && !erreur; i++ )
		{

			inter1.GetInterval ( i, borneInf1, borneSup1 );
			inter3.GetInterval ( i, borneInf2, borneSup2 );

			if ( borneInf1 != borneInf2 || borneSup1 != borneSup2 )
			{
				cout << "Test " << nTest << " : Erreur" << endl;
				erreur = true;
			}

		}

		if ( !erreur )
		{
			cout << "Test " << nTest << " : OK" << endl;
		}
	}
	else
	{
		cout << "Test " << nTest << " : Erreur" << endl;
	}

	return 1;

} //----- fin de main
