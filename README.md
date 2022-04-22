# optimisation

## Faire fonctionner les dépendances

Allez dans SDL2/lib/x64 et copiez-collez le fichier .dll (SDL2.dll) dans le dossier cmake-build-debug de votre projet. <br>
Puis allez dans SDL2_TTF/lib/x64 et copiez-collez les fichiers .dll (libfreetype-6.dll, SDL2_ttf.dll et zlib1.dll) dans le dossier cmake-build-debug de votre projet.



## TODO
--> Bug avec la gestion de mémoire en sortie de la fonction affichage de la classe Interface, donc passage des vecteurs client et tournees en membre pour contourner la suppression...
