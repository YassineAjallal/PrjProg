/* date */
typedef struct Date{
    int dd;
    int mm;
    int yy;
}date;

/* voitue */

typedef struct Voiture{
    int idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char EnLocation[4];
}voiture;

/* contrat de location */

typedef struct contratLocation {
    float numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date fin;
    int cout;
}contrat;

/* client */

typedef struct Client{
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
}client;
