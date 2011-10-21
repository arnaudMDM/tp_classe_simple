/*************************************************************************
 IntervalSet  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par Robin Gicquel et Arnaud Mery de Montigny
 *************************************************************************/

//---------- Interface de la classe <IntervalSet> (fichier IntervalSet.h) ------
#if ! defined ( INTERVALSET_H_ )
#define INTERVALSET_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <IntervalSet>
// La fonction de cette classe est de gérer un nombre virtuellement infini
// d'intervalles, c'est à dire un ensemble d'intervalles disjoints. On sera en
// réalité limité par la mémoire disponible de la machine.
// On entend par « intervalle » un intervalle fermé au sens mathématique dont
// les bornes sont des nombres entiers relatifs. Les deux bornes peuvent être
// identiques.
//
//------------------------------------------------------------------------ 

class IntervalSet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	void Display ( ) const;
	// Mode d'emploi :
	//	Affiche ligne par ligne chaque intervalle contenu dans l'objet sous la
	// forme "[x, y]" si l'ensemble contient au moins un intervalle.
	// Puis on affiche sur une dernière ligne le nombre d'intervalles
	// contenus dans l'ensemble sous la forme "Nombre d'intervalles : u", u
	// étant le nombre d'intervalles.
	//	L'objet appelant n'est pas modifié.
	//
	// Contrat :
	//	aucun

	bool Add ( long lLeft, long lRight );
	// Mode d'emploi :
	//	Le premier paramètre désigne la borne inférieure et le deuxième la borne
	// supérieure. La borne inférieure peut être égale à la borne supérieure.
	// 	Si l'intervalle saisi ne recoupe aucun des intervalles déjà
	// contenus dans l'objet, il est ajouté à l'objet de façon ordonné. La borne
	// inférieure de l'intervalle du paramètre est supérieure aux bornes
	// inférieures des autres intervalles placés derrière, et inversement.
	// 	Il est à noter qu'une borne d'un intervalle ne peut pas être la borne
	// d'un autre intervalle de l'objet. Renvoie vrai si l'ajout a été effectué
	// ou faux dans le cas contraire.
	//
	// Contrat :
	//	aucun

	bool Add ( IntervalSet& is );
	// Mode d'emploi :
	//	Le paramètre est un autre ensemble d'intervalles.
	//	La fonction ajoute tous les intervalles de is à l'ensemble de l'objet
	// appelant si et seulement si tous les éléments peuvent être ajoutés.
	// 	Elle renvoie la valeur booléenne vrai si on peut tout ajouter.
	// Dans le cas contraire, elle renvoie faux.
	//
	// Contrat :
	//	aucun

	bool Remove ( long lPos );
	// Mode d'emploi :
	//	Efface un intervalle de l'ensemble en fonction du paramètre lPos
	// qui représente la position de l'intervalle par rapport aux autres
	// intervalles et renvoie vrai. Le tri est fait par rapport à la
	// valeur de la borne inférieure ou supérieure. Si la valeur de lPos ne
	// correspond pas à une position de l'intervalle, la fonction renvoie faux
	// et ne supprime rien.
	//
	// Contrat :
	//	aucun

	long Count ( ) const;
	// Mode d'emploi :
	//	Renvoie le nombre d'intervalles contenus dans l'ensemble.
	//
	// Contrat :
	//	aucun

	bool GetInterval ( long lPos, long& lLeft, long& lRight ) const;
	// Mode d'emploi :
	//	Renvoie vrai si lPos correspond à une position d'un intervalle
	// et affecte également la borne inféieure de cet intervalle à
	// lLeft et celle de la borne supérieure à lRight.
	//	Si lPos ne correspond à aucun intervalle, la fonction renvoie faux et
	// n'affecte aucune valeur.
	//
	// Contrat :
	//	aucun

	IntervalSet& Union ( IntervalSet& is );
	// Mode d'emploi :
	//	Renvoie un nouvel objet IntervalSet qui est le résultat de
	// l'union de l'ensemble de l'objet appelant cette méthode et de l'ensemble
	// is. Il s'agit d'une union au sens mathématique.
	//
	// Contrat :
	//	aucun

	IntervalSet& Intersection ( IntervalSet& is );
	// Mode d'emploi :
	//	Renvoie un nouvel objet IntervalSet qui est le résultat de
	// l'intersection de l'ensemble de l'objet appelant cette méthode et de
	// l'ensemble is. Il s'agit d'une intersection au sens mathématique.
	//
	// Contrat :
	//	aucun

	//------------------------------------------------- Surcharge d'opérateurs
	IntervalSet & operator = ( const IntervalSet & is );
	// Mode d'emploi :
	//	Libère la mémoire utilisée par les éléments dynamiques du membre de
	// gauche et réalise une copie du membre de droite dans le membre de gauche
	//
	// Contrat :
	//	aucun

	//-------------------------------------------- Constructeurs - destructeur
	IntervalSet ( const IntervalSet& is );
	// Mode d'emploi (constructeur de copie) :
	//	Crée un objet ayant les mêmes caractéristiques que l'objet passé en
	// paramètre.
	//
	// Contrat :
	//	aucun

	IntervalSet ( );
	// Mode d'emploi :
	//	Crée un objet avec des valeurs par défaut, c'est à dire aucun
	// intervalle.
	//
	// Contrat :
	//	aucun

	virtual ~IntervalSet ( );
	// Mode d'emploi :
	//	Destructeur de la classe.
	//
	// Contrat :
	//	aucun

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés
	long borneInf; // borne inférieure de l'intervalle
	long borneSup; // borne supérieure de l'intervalle
	long nbInter; // nombre d'intervalles contenus dans l'ensemble
	IntervalSet *suivant; // pointeur sur l'élément suivant de l'ensemble
};

//--------------------------- Autres définitions dépendantes de <IntervalSet>

#endif // INTERVALSET_H_
