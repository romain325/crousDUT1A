/***********************tri.c*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crous.h"

/*************************TRI RAPIDE PRENANT EN COMPTE UN TABLEAU DE POINTEURS DE LOG****************************/
//le tri se fait en fonctions de la variable "nomCite"
void triRapide(LOGEMENT** tab,int n)
{
	int i=0,j=n-2;
	LOGEMENT *aux1,*aux2;
	if (n<=1) return;
	aux2 = tab[n-1];
	while(i<=j)
	{
		while(strcmp(tab[i]->nomCite,aux2->nomCite)<=0 && i<n) i++;
		while(strcmp(tab[j]->nomCite,aux2->nomCite)>=0 && 0<=j) j--;
		if (i<j)
		{
			aux1 = tab[i];
			tab[i] = tab[j];
			tab[j] = aux1;
		}
	}
	tab[n-1] = tab[i];
	tab[i] = aux2;

	triRapide(tab,i);
	triRapide(tab+i+1,n-i-1);
	return;
}

/*****************************RECHERCHE DICHOTOMIQUE DE LETUDIANT*********************************************/
//on part de la position centrale du tableau puis affine à chaque tour jusqu'à obtenir la valeur souhaité
//alors à ce moment là on décide de retourner la position de l'élement dans le tableau etu
int rechDichoEtu(ETUDIANT* tEtu[],int n,char val[])
{
	int inf=0,sup=n-1,mid;		
	while(inf<=sup)
	{
		mid = (inf+sup)/2;
		if (strcmp(tEtu[mid]->idEtudiant,val) == 0)
			return mid;
		if (strcmp(val,tEtu[mid]->idEtudiant) < 0)
			sup = mid-1;
		else
			inf = mid+1;
	}
	return -1;
}

/*******************************************TRI PAR FUSION DEMANDES************************************************/
void copieAttrib(DEMANDE* T[],int i, int j, DEMANDE* R[]) //copie des informations dans un nouveau tableau
{
	int k = 0;
	while(i<j)
	{
		R[k] = T[i];
		i=i+1;k=k+1;
	}
}

//La variable type tri definit selon quelle parametres on tri --> echelon ou idDemandes
void fusionAttrib(DEMANDE* R[],int n,DEMANDE* S[],int m, DEMANDE* T[],int typeTri)
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if (typeTri == 1 )							//tri en fonction de l'échelon
		{
			if (R[i]->echelon > S[j]->echelon)
			{
				T[k] = R[i];
				i++;k++;
			}
			else
			{
				T[k] = S[j];
				k++;j++;
			}
		}
		if (typeTri == 2)							//tri en fonction de l'id de la demande
		{
			if (strcmp(R[i]->idDemande,S[j]->idDemande)<0)
			{
				T[k] = R[i];
				i++;k++;
			}
			else
			{
				T[k] = S[j];
				j++;k++;
			}
		}
		if (typeTri != 1 && typeTri != 2)
		{
			printf("Erreur indication de la valeur a comparé // sortie // toute données non sauvegardés est perdus\n");
			exit(1);
		}
	}
	while(i<n)
	{
		T[k] = R[i];
		i++;k++;
	}
	while(j<m)
	{
		T[k] = S[j];
		j++;k++;
	}
}

void triFusionAttrib(DEMANDE* T[], int n,int typeTri)
{
	DEMANDE **R,**S;
	if(n == 1) return;
	R = (DEMANDE**) malloc((n/2)*sizeof(DEMANDE*));
	S = (DEMANDE**) malloc((n-n/2)*sizeof(DEMANDE*));
	if (R == NULL || S == NULL)
	{
		printf("Erreur Allocation Espace // Sortie du Programme\nVos données non enregistrés seront perdus\n");
		exit(1);
	}
	copieAttrib(T,0,(n/2),R);
	copieAttrib(T,(n/2),n,S);
	triFusionAttrib(R,(n/2),typeTri);
	triFusionAttrib(S,(n-n/2),typeTri);
	fusionAttrib(R,(n/2),S,(n-n/2),T,typeTri);
	free(R);
	free(S);
	return;
}

/***************RECHERCHE DICHOTOMIQUE DANS UN TABLEAU DE POINTEURS DE DEMANDES*********************/
	//recherche prenant en compte l'idDemande
int rechDichoDem(DEMANDE* tDem[],int n,char val[])
{
	int inf=0,sup=n-1,mid;		
	while(inf<=sup)
	{
		mid = (inf+sup)/2;
		if (strcmp(tDem[mid]->idDemande,val) == 0)
			return mid;
		if (strcmp(val,tDem[mid]->idDemande) < 0)
			sup = mid-1;
		else
			inf = mid+1;
	}
	return -1;
}
	//recherche prenant en compte l'idDemande
int rechDichoDemEtu(DEMANDE* tDem[],int n,char val[])
{
	int inf=0,sup=n-1,mid;		
	while(inf<=sup)
	{
		mid = (inf+sup)/2;
		if (strcmp(tDem[mid]->idEtudiant,val) == 0)
			return mid;
		if (strcmp(val,tDem[mid]->idEtudiant) < 0)
			sup = mid-1;
		else
			inf = mid+1;
	}
	return -1;
}

/***********RECHERCHE LOGEMENTS************/
int rechLog(DEMANDE dem,LISTE tLog, int nbLog,ETUDIANT etu)
{
	int i;
	for (i = 0; i < nbLog; ++i)
	{
		if (tLog->log.dispo == TRUE)
		{
			if((etu.handicap == 1 && tLog->log.adaptHandicap == 1) || (etu.handicap == 0))
			{
				if (strcmp(dem.citeSouhait,tLog->log.nomCite)==0 && strcmp(dem.typeLogementSouhait,tLog->log.typeLogement)==0)
				{
					return i;
				}
			}
		}
		tLog = tLog->suiv;
	}
	return -1;
}

/*******************************************TRI PAR FUSION EtudiantS************************************************/
void copieAttribEtu(ETUDIANT* T[],int i, int j, ETUDIANT* R[]) //copie des informations dans un nouveau tableau
{
	int k = 0;
	while(i<j)
	{
		R[k] = T[i];
		i++;k++;
	}
}

void fusionAttribEtu(ETUDIANT* R[],int n,ETUDIANT* S[],int m, ETUDIANT* T[])
{
	int i=0,j=0,k=0;
	while(i<n && j<m)
	{
		if (strcmp(R[i]->idEtudiant,S[j]->idEtudiant)<0)
		{
			T[k] = R[i];
			i++;k++;
		}
		else
		{
			T[k] = S[j];
			k++;j++;
		}
	}
	while(i<n)
	{
		T[k] = R[i];
		i++;k++;
	}
	while(j<m)
	{
		T[k] = S[j];
		j++;k++;
	}
}

void triFusionAttribEtu(ETUDIANT* T[], int n)
{
	ETUDIANT **R,**S;
	if(n == 1) return;
	R = (ETUDIANT**) malloc((n/2)*sizeof(ETUDIANT*));
	S = (ETUDIANT**) malloc((n-n/2)*sizeof(ETUDIANT*));
	if (R == NULL || S == NULL)
	{
		printf("Erreur Allocation Espace // Sortie du Programme\nVos données non enregistrés seront perdus\n");
		exit(1);
	}
	copieAttribEtu(T,0,(n/2),R);
	copieAttribEtu(T,(n/2),n,S);
	triFusionAttribEtu(R,(n/2));
	triFusionAttribEtu(S,(n-n/2));
	fusionAttribEtu(R,(n/2),S,(n-n/2),T);
	free(R);
	free(S);
	return;
}