/***********************crous.h*****************************/
/******************STRUCTURES**********************/
typedef enum{FALSE,TRUE}BOOL;
typedef struct 
{
	char idLogement[9];				
	int dispo;					//Savoir si la chambre est dispo, si non alors idOccupant=0
	char idOccupant[9];			//idOccupant actuelle ou 0 si chambre vide
	char typeLogement[3];		//CHECK --> seul rep accepter ["T1","T2","CH","ST"]
	int adaptHandicap;
	char nomCite[25];
}LOGEMENT;						//Recup dans logements.don et mettra tout dans un tab pointeurs de struct


typedef struct 					//trié selon l'idEtudiant, donne tout les etudiants connus du CROUS
{
	char idEtudiant[9];
	char sexe;					//Uniquement "H","F" pour des raisons de simplifications
	char nom[16];
	char prenom[12];
	int boursier;				//Si non boursier alors echelon = -1
	int echelon;				//0 pour 0bis, 1pour1,2pour2,etc...
	int handicap;
}ETUDIANT;						//Recup dans etudiants.don et mettra tout dans un tab pointeurs de struct


typedef struct 					//Trié par ordre décroissant d'échelon de bourse des étudiants demandeurs
{
	char idDemande[9];
	char idEtudiant[9];
	int echelon;				//-1si non boursier,0 pour 0bis, 1pour1,2pour2,etc...
	char citeSouhait[25];
	char typeLogementSouhait[3];//CHECK --> seul rep accepter ["T1","T2","CH","ST"]
}DEMANDE;						//Recup dans demandeEnAttente.don et mettra tout dans un tab pointeurs de struct

typedef struct maillon
{
	LOGEMENT log;
	struct maillon *suiv;
}MAILLON, *LISTE;

/*********GLOBAL ET AFFICHAGE***********/
void global(void);
int affichLancement(void);
int choix(void);

/*****GESTION DES LISTES*****/
LISTE nvListe(void);
LISTE insertionEnTete(LISTE l, LOGEMENT x);
int vide(LISTE l);
LOGEMENT tete(LISTE l);
void afficherListeChainee(LISTE l);
LISTE suppressionEnTete(LISTE l);
LISTE insererEnQueue(LISTE l, LOGEMENT log);
LISTE suppression(LISTE l,char id[8]);
LISTE inserer(LISTE l, LOGEMENT log);
LISTE insererPNom(LISTE l, LOGEMENT log);
int longueurListe(LISTE l);

/************LECTURE & ENREGISTREMENT FILE************/
LOGEMENT fLireLogement(FILE* flot);
void fEcrireLogement(LOGEMENT log);
LISTE fLireTabLogement(int* nb);
void fEnregistrLogement(LISTE tLog);
ETUDIANT* fLireEtudiant(FILE* flot);
void fEcrireEtudiant(ETUDIANT* etu);
ETUDIANT** fLireTabEtudiant(int* nb);
void fEnregistrEtudiant(ETUDIANT** tEtu, int nbEtu);
DEMANDE* fLireDemande(FILE* flot);
void fEcrireDemande(DEMANDE* dem);
DEMANDE** fLireTabDemande(int* nb);
void fEnregistrDemande(DEMANDE** tDem, int nbDem);

/***********LOGEMENT DISPONIBLE************/
LISTE logDispo(LISTE l,int nb);
void triRapide(LOGEMENT** tab,int n);
void affichLogDispo(LOGEMENT** logDisp,int n);

/**********LOGEMENT OCCUPE*************/
void logOccup(LISTE tLog, int nbL, ETUDIANT* tEtu[],int nbE);
int rechDichoEtu(ETUDIANT* tEtu[],int n,char val[]);
void triFusionAttrib(DEMANDE* T[], int n,int typeTri);

/************ATTRBUTIONS DES LOGEMENTS SELON DEMANDES**************/
void fAffichDemande(DEMANDE* tDem[],int nb);
void attributionLogements(DEMANDE* tDem[],int* nbDem,ETUDIANT* tEtu[], int nbEtu,LISTE tLog, int nbLog);
int rechLog(DEMANDE dem,LISTE tLog, int nbLog,ETUDIANT etu);
void attribValid(char idEtu[], LISTE tLog, int pos);
void supprDemande(DEMANDE** tDem, int pos,int* n);

/***************NOUVELLE DEMANDE // NOUVEAU ETUDIANT***************/
void typeLogementLieu(void);
DEMANDE** nvlDemande(ETUDIANT** tEtu,int* nbEtu,DEMANDE** tDem,int* nbDem);
int rechDichoDem(DEMANDE* tDem[],int n,char val[]);
ETUDIANT** creatEtu(ETUDIANT** tEtu, int* nbEtu);
DEMANDE** ajoutDem(DEMANDE** tDem,int* nbDem,char idEtu[],int echelon,char citeSouhait[],char logSouhait[]);
int rechDichoDemEtu(DEMANDE* tDem[],int n,char val[]);
int giveRandNum(void);
void copieAttribEtu(ETUDIANT* T[],int i, int j, ETUDIANT* R[]);
void fusionAttribEtu(ETUDIANT* R[],int n,ETUDIANT* S[],int m, ETUDIANT* T[]);
void triFusionAttribEtu(ETUDIANT* T[], int n);

/*****************ANNULATION D'UNE DEMANDE*******************/
int annulDem(DEMANDE ** tDem,int n);
void decalerGauche (DEMANDE **tDem, int n,int pos);

/*****************LIBERATION D'UN LOGEMENT*******************/
void libLogement(LISTE tLog);