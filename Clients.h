/*---------------------------- lister des clients ------------------------*/

void listerClient(FILE *file) {
	system("cls");
   client client;

   fseek(file,0,SEEK_SET);

   while (fread(&client,sizeof(client),1,file) != 0) {
     printf("identificateur du client .....: %d\n",client.idClient  );
     printf("nom du client........ ........: %s\n",client.nom  );
     printf("prenom du client .............: %s\n",client.prenom  );
     printf("cin du client ................: %d\n",client.cin  );
     printf("adresse : .....: %s\n",client.adresse  );
     printf("telephone : .....: %d\n",client.telephone  );
     printf("\n ================================ \n");
   }
   fseek(file, 0, SEEK_SET);
   fclose(file);
   main();
}

/*--------------------------- ajouter un client --------------------------------*/

void ajouterClient (FILE *file) {
  client client;
  printf("id : ");
  scanf("%d",&client.idClient);
  printf ("nom  : ");
  scanf ("%s", &client.nom);
  printf ("prenom : ");
  scanf ("%s", &client.prenom);
  printf("Cin (nbre) : ");
  scanf("%d",&client.cin);
  printf("adresse : ");
  scanf("%s",&client.adresse);
  printf("telephone : ");
  scanf("%d",&client.telephone);
  fseek(file, 0, SEEK_END);
  fwrite (&client, sizeof(client), 1, file);
  fseek(file, 0, SEEK_SET);
  fclose(file);
  system("cls");
  main();
}

/*--------------------------- modifier un client --------------------------------*/

void modifierClient(FILE *file){

    client client ;
    int trouve = 0;
    int id;
    char test;
    printf("Donnez le id : ");
    scanf("%d",&id);
    fseek(file, 0, SEEK_SET);
    
     /* verification de id*/
    while (fread(&client, sizeof(client), 1, file) != 0 && trouve==0) {
        if (client.idClient == id) {
            trouve = 1 ;
            break ;
        }
    }

    if(trouve == 0){
          printf("Ce client  n'existe pas\n");
    }else{

             fseek(file,-(sizeof client),SEEK_CUR) ;
             printf("Les entrees anciennes : \n");
             printf("nom du client ........ ........: %s\n",client.nom  );
             printf("prenom du client .............: %s\n",client.prenom );
             printf("cin de client ................: %d\n",client.cin  );
             printf("l adresse : .....: %s\n",client.adresse  );
             printf("le thelephone : .....: %d\n",client.telephone  );
             printf("\n\n qu'est ce que tu veux changer ? \n ============================= \n ");

            client.idClient = id;
             /* modifier le nom */
             printf("nom ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv nom : ");
                scanf("%s",&client.nom);
             }else strcpy(client.nom , client.nom);
             printf("\n");

             /* modifier le prenom */
             printf("prenom ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv prenom : ");
                scanf("%s",&client.prenom) ;
             }else strcpy(client.prenom,client.prenom);
             printf("\n");

             /* modifier le CIN */
             printf("CIN ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv CIN : ");
                scanf("%d",&client.cin) ;
             }else client.cin = client.cin ;
             printf("\n");

             /* modifier l'adresse */
             printf("adresse ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv adresse : ");
                scanf("%s",&client.adresse) ;
             } else strcpy(client.adresse,client.adresse);
             printf("\n");

             /* modifier le telephone */
             printf("telephone ? : (o/n) \t ") ;
              scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv telephone : ");
                scanf("%d",&client.telephone);
             }else client.telephone = client.telephone ;
             printf("\n");

             /* sauvegarder les modification*/
             fwrite(&client,sizeof(client),1,file);
        }
        fseek(file, 0, SEEK_SET);
        fclose(file);
        system("cls");
		main();
}

/*--------------------------- supprimer un client --------------------------------*/

void supprimerClient(FILE *file,FILE *tempC){
   client client ;
   int trouve = 0;
   int id;
   printf("Donnez le id a supprimer : ");
   scanf("%d",&id);

   fseek(file, 0, SEEK_SET);

   // verification de id
  while (fread(&client, sizeof(client), 1, file) != 0 && trouve==0) {
    if (client.idClient == id){
        trouve = 1 ;
        break ;
    }
  }

  if (trouve == 0){
    printf("Ce client n'existe pas\n");
    system("pause");
    main();
  }

    fseek(file, 0, SEEK_SET);
    
    /* copier les voitures qui n'est pas supprimer dans le fichier "renommerC" */
    while(fread(&client, sizeof(client), 1, file))
	{
		if(client.idClient==id)
		{
            continue;
		}
		else
		{
			fwrite(&client,sizeof(client),1,tempC);
		}
	}
	fclose(file);
    remove("Client.txt");
    fclose(tempC);
    rename("renommerC.txt","Client.txt");
    system("cls");
    main();
}
