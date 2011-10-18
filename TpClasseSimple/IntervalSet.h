/*************************************************************************
 IntervalSet  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par rgicquel
 *************************************************************************/

//---------- Interface de la classe <IntervalSet> (fichier IntervalSet.h) ------
#if ! defined ( INTERVALSET_H_ )
#define INTERVALSET_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <IntervalSet>
//
//
//------------------------------------------------------------------------ 

class IntervalSet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	void Display ( );
	// Mode d'emploi :
	//	Affiche ligne par ligne chaque intervalle contenu dans l'objet sous la forme "[x, y]".
	//	Si l'objet ne contient aucun intervalle, la mention "Aucun intervalle" est affichée.
	//	L'objet appelant n'est pas modifié.
	// Contrat :
	//	aucun

	bool Add ( long lLeft,long lRight );
	// Mode d'emploi :
	//	Le premier désigne la borne inférieure et le deuxième la borne supérieure. Si l'intervalle saisi ne recoupe aucun des intervalles déjà contenus dans l'objet, il est ajouté à l'objet. Il est à noter qu'une borne d'un intervalle ne peut pas être la borne d'un autre intervalle de l'objet.
	// Contrat :
	//	aucun

	bool Add ( IntervalSet& is );
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	bool Remove ( long lPos );
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	long Count ( ) const;
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	bool GetInterval ( long lPos, long& lLeft, long& lRight ) const;
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	IntervalSet& Union ( IntervalSet& is );
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	IntervalSet& Intersection ( IntervalSet& is );
	// Mode d'emploi :
	//
	// Contrat :
	//	aucun

	//------------------------------------------------- Surcharge d'opérateurs

	//-------------------------------------------- Constructeurs - destructeur
	IntervalSet ( const IntervalSet& is );
	// Mode d'emploi (constructeur de copie) :
	//	Crée un objet ayant les mêmes caractéristiques que l'objet passé en paramètre
	// Contrat :
	//	aucun

	IntervalSet ( );
	// Mode d'emploi :
	//	Crée un objet avec des valeurs par défaut, c'est à dire aucun intervalle
	// Contrat :
	//	aucun

	virtual ~IntervalSet ( );
	// Mode d'emploi :
	//	Destructeur classique
	// Contrat :
	//	aucun

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	bool addRecursive ( long lLeft, long lRight );
	// Mode d'emploi :
	//	Destructeur classique
	// Contrat :
	//	appelé dans la méthode Add

	int updateNbInter ( );
	// Mode d'emploi :
	//	Met à jour le nombre d'intervalles de chaque élément de liste chaînée
	// Contrat :
	//	L'objet ne doit pas représenter un ensemble vide

	//----------------------------------------------------- Attributs protégés
	long borneInf;
	long borneSup;
	long nbInter;
	IntervalSet *suivant;
};

//--------------------------- Autres définitions dépendantes de <IntervalSet>

#endif // INTERVALSET_H_
