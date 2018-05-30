% Documentation utilisateur de chord V
% Gilles Maire 
% Mai 2018 


# Introduction 


## Présentation 


- ChordV permet de produire différents types de fichiers PDF pour une 
liste de  chansons
- ChordV fournit :
    - un éditeur de texte avec colorisation syntaxique et insertion des 
    balises au format cho
    - un gestionnaire d'accords et d'une base d'accords guitare 
    permettant d'ajouter ou d'insérer les accords
    - quatre processeurs permettant de générer un livre contenant les 
    paroles sans les accords, un livre avec
    accords et paroles, un livre avec les grilles d'accords
- Pour chacun des modes la gestion des options permet de faire les 
réglages idoines
   - **Texte :** dans ce mode, les paroles seules apparaissent, sans 
   aucune représentation d'accord
   - **Lyrics :** dans ce mode, le texte et les accords sont affichés.
   - **Accords :** dans ce mode, les accords ne sont affichés. Il est 
   utile pour les musiciens d'accompagnement.
   - **Mémoire :** dans ce mode, un monitoring des paroles est proposé
   pour permettre le suivi des paroles

- ChordV utilise un langage de balises très efficace et simple:

~~~
{title:Let it be}

{subtitle: Lyrics ansd music :  Paul McCartney, John Lennon}
{Subtitle: Apple Label}
{columns:1 }
When I  [C] find myself in  [G]  times of trouble
Am Mother  [G] Mary  [F]  comes to me
[C] Speaking words of  [G] wisdom, let it  [F | C/E] be.       [Dm7][C]
And  [C] in my hour of  [G]  darkness
She is  [Am] standing  [G] right in   [F]  front of me
[C] Speaking words of  [G] wisdom, let it  [F | C/E] be.       [Dm7][C]
~~~~


## Le mode batch et le mode graphique


- Sans aucun argument chordV est lancé avec une interface graphique
- Avec l'argument -t chordV ne lance pas l'interface graphique et 
produira les  PDF pour la configuration par défaut
- Vous pouvez également lancer chordV avec un argument fichier.chop  
pour l'ouvrir automatiquement au démarrage.


# Les préférences du logiciel


## De l'utilité des préférences


- Les préférences permettent de définir les options pour tous les 
recueils de chanson afin de rendre homogène une collection de recueils.
- Imaginons que vous souhaitiez construire un recueil des chansons de 
Brassens, un recueil des chansons de Renaud et un recueil des chansons
de Jeanne Chéral. Pour chacun de ces recueils, vous pourrez choisir 
les différentes types de sortie que vous souhaitez et définir à votre
guise chaque sortie, mais vous pouvez vouloir définir les mêmes 
formats pour chacun d'eux, ou au moins quelques options communes dans 
les polices de caractères ou autre. C'est dans les préférences que vous 
pourrez  régler ces options globales, quitte à pouvoir les adpater à 
chacun des artistes par la suite.
- Il faut noter qu'il existe des raccourcis de préférences appelés 
gadgets de préférence.
   - L'un vous permet de revenir aux choix initiaux du logiciels au 
   cas où vos essais ne seraient pas satisfaisants
   - L'un vous permet de définir un réglage pour un artiste comme le 
   réglage par défaut dans l'avenir.

## Le menu des préférences

- On accède aux préférences par le menu Préférence ou par le racourci 
clavier CTRL + O comme le montre la figure suivante

![Le menu des préférences ](./img/menupreferences.png)


## Les options générales des préférences

![Options générales](./img/preferencegeneral.png)

1. Vous pouvez choisir la langue du logiciel. Si votre langue de figure
pas dans la liste, vous pouvez fabriquer un fichier de traduction
(voir la partie [traduction](#traduction-du-logiciel-dans-une-langue) )
2. Sélectionner le système de mesure qui vous convient le mieux entre 
cm, mm et pouce
3. ChordV lance un lecteur PDF quand vous voulez visualiser 
le livré généré par l'application. Il faut renseigner dans cette zone 
le nom du programme 
4. Le nom de l'auteur du livret peut-être entré ici. Il sera utilisé
dans la production des documents.


## Les options de chaque mode de livret

Ces options ne sont pas forcéments exactement les mêmes pour chaque 
livret, en effet en mode texte la police des accords n'existe pas 
puisque dans ce mode les accords n'existent pas. Nous allons 
séparer la présentation des options communes et celles spécifiques 
à chaque mode.

On trouve deux onglets l'un appelé Document et l'autre contenu pour
chacune des 

### Les options communes de l'onglet Document


![Options générales](./img/preferencetext.png)

1. Zone de sélection de la largeur. Si vous mettez ici des valeurs 
correspondants à un format existant, ce format sera affiché dans la zone
3. 
2. Zone de sélection de la hauteur. Si vous mettez ici des valeurs 
correspondants à un format existant, ce format sera affiché dans la zone
3. Cette zone permet de choisir un format de PDF par un nom IS0. Si 
vous sélectionnez un format par ce menu, vous verrez les tailles
correspondantes s'afficher dans les zones 1 et 2
4. A l'italienne inverse les hauteurs et les largeurs
5. Permet de sélectionner la police par défaut du document. Se référer
à la documentation relative à la 
[Sélection des police](#sélection-des-polices)
6. Permet de sélectionner la police relative aux titres de chaque page.
Si vous sélectionnez une couleur de fond (Se référer
à la documentation relative à la 
[Sélection des police](#sélection-des-polices), un cadre de la couleur
sélectionnée encadrera le titre sur toute la largeur de la page.
7. Permet de sélectionner la police relative aux sous titres de chaque 
page. Si vous sélectionnez une couleur de fond (Se référer
à la documentation relative à la 
[Sélection des police](#sélection-des-polices), un cadre de la couleur
sélectionnée encadrera le titre sur toute la largeur de la page.
8. Sélectionne le mode recto ou recto verso. Si vous sélectionnez le
mode recto verso, les numéros de pages s'ils sont excentrés à droite
seront excentrés à gauche une page sur deux.
9. En indiquant la couleur du papier, les couleurs de cadre des titres
et des sous titres s'ils sont de cette couleur ne seront pas dessinés.
Cela évite un effacement des caractères qui pourraient setrouver sous 
le cadre.
10. Cette zone permet de numéroter les pages avec le numéro à droite, 
au centre ou à gauche
11. Permet de choisir le style de numérotation de page 1, - 1 - ou 1/n
12. Cette zone vous permet de choisir la police de caractères des 
numéros de page. Si la la couleur de font de page n'est pas identique 
à la couleur du papier un cadre sera dessiné autour du numéro de page.
13. Permet de définir la marge horizontale
14. Permet de définir la marge verticale

### Les options communes de l'onglet Contenu 

![Options générales partie contenue](./img/preferencestextcontent.png)

1. Le fichier PDF comporte une couverture
2. La police de caractères de la couverture est positionnée 
3. Le titre peut être au tiers de la hauteur, à la moitié ou au 2/3
4. Sélection d'une image optionnelle pour la couverture
5. Mode compression de la table des matières activé
6. Nombre de colonnes de la table des matières
7. Police de caractères uitilisée pour la table des matières
8. Caratères utilisés entre le nom du titre et la page dans la table
des matières
9. Position de la table des matières, au début, à la fin du document ou 
pas de table des matières
10. Extension ajoutée au fichier de sortie
11. Espacement vertical 
12. Ouverture du PDF en mode plein écran
13. Forcer les titres en majuscule


### Les préférences du mode mémoire

Le mode aide mémoire ou monitoring des paroles permet d'afficher 
les paroles en suivant les informations du fichier de chanson, notamment
- les balises {tempo:xx} qui donnent le tempo de chaque chanson. Si 
la balise tempo est absente d'un morceau, elle sera arbritrairement
forcée à la valeur 120
- à la balise time de la forme x/y qui indique le nombre de temps de
chaque mesure. Si cette balise est absente, elle sera arbitrairement 
forcée à la valeur 4/4

![Options générales mode mémoire](./img/ConfigurationMemory.png)

1. Permet de sélectionner la police de caractères ainsi que sa couleur 
et la couleur du fond telle qu'elle apparait dans la zone 5
2. Permet d'indiquer si la fenêtre de monitoring sera en haut de l'écran,
au milieu ou à droite. Si le mode plein écran est sélectionné ce mode
ne sera plus accessible. Ce mode est destiné au mode enregistrement d'une
chanson quand le chanteur veut suivre la progresssion de son enregistrement
sur son logiciel d'enregistrement
3. Mode plein écran plutôt destiné au karaoké, bien qu'on puisse projeter
une vidéo et ou des images pendant que la musique est activée avec le mode 
image en bas de l'écran.
4. Deux lignes sont affichée, la ligne plus brillante sur les paroles en 
cours et la ligne plus foncée sur les paroles suivantes. Si ce mode
n'est pas sélectionné, une seule ligne est affichée.
5. Rendu de la police de caractères
6. Chaque temps est matérialisé par l'affichage d'une bulle rouge pour
le premier temps et d'une bulle verte pour les autres temps.
7. Un click sonore est activé sur chaque temps
8. Réglage du volume du click
9. Le premier temps sonore est plus marqué que les autres temps
10. Avance de l'affichage, réglage de l'avance de l'affichage du temps
sur les paroles pour permettre au chanteur de lire légèrement à l'avance
11. Nombre de mesures avant de démarrer l'enregistrement.


3. Mode plein écran 


## Les conventions 

### Sélection des polices 

![Sélection des polices](./img/fontselection.png)

La sélection des polices permet de sélectionner la famille police 
souhaitée, sa taille, son style et toutes les options traditionnelles
aux quelles sont ajoutés : 
    - la couleur du fond
    - la couleur de la police
La sélection d'une couleur changera la couleur du bouton afin de 
vous montrer la couleur qu'il recèle
Une explication sur la couleur de fond est nécessaire.


# La fenêtre d'édition 

## Présentation 

### La fenêtre d'édition 

![La fenêtre d'édition](./img/editor.png)

1. Le menu édition permet d'accéder aux fonctions rechercher remplacer
et de zoomer la police de caractères. En regard les items du menu vous
disposez de raccourcis clavier. 
2. Les icones permettent d'insérer les Titres de couverture, les mesures
et toutes les informations qui sont surlignées en violet sur la figure.
3. La zone de texte vous permet de rentrer les chansons au format 
chord pro 
4. La partie log affiche des messages d'erreur étiquetés en rouge
et des messages de succès étiquetés en vert.
5. Quand vous sélectionner un accord, en actionnant la molette de la
souris vers le haut ou le bas vous montez ou descendez la durée d'un 
accord. Ainsi on passe du [Do#x2] au [Do#] puis au [Do:2] en tournant 
la molette vers soi.
6. Un navigateur table des matière permettant de se rendre directement à
la chanson désirée

### Le langage à balise de chord pro 

On peut trouver étrange qu'un logiciel moderne ne présente pas une
interface Wysiwyg, c'est à dire dont l'aspect ressemble à la sortie
papier. En fait ChordV prend un seul format d'entrée et il est capable
de générer un livret de texte, un livret de texte et accords, un livret 
de grille d'accords et des aide mémoires. Dans quel mode fallait 
il choisir de travailler ? Nous avons choisi le mode à balise qui nous 
semblé un format pivot. 

En plus ce format pivot est écrit dans le langage chord pro plus des 
extensions utiles au programme. Ainsi vous pourrez charger dans ChordV 
l'ensemble des fichiers chord pro disponibles dans les resources 
musicales libres du net.


## Insertion des accords dans l'éditeur

En double cliquant sur le texte la fenêtre d'inclusion d'accord vous 
permet de sélectionner un accord par l'appui sur le bouton Inserer
l'accord. Cette action peut également être optenue par l'appui de
la touche F4 (alors que la touche F3 permet d'entrer dans le mode
de gestion des accords)

Vous pouvez modifier le tempo par l'emploi de la molette de la souris 
en maintenant la touche SHIFT appuyée dans l'éditeur.

# Le menu des outils

## Le menu des préférences 

## Gadget des préférences

## Définition des accords 

### Présentation 

La fenêtre de définition des accords se décompose en quatre onglets :
- La définition de l'accord qui permet de trouver un accord à partir 
des position des doigts sur le manche 
- Un module de gestion des accords permettant la visualisation, la 
modification ou la suppression de chaque accord
- Un module permettant d'approuver chaque accords non approuvé
- Un module permettant d'importer une liste d'accods contenus dans un 
fichier texte

### La définition d'un accord

![Définition de l'accord ](./img/chorddefinition.png)

1. Sélection des cases appuyées sur le manche
2. Sélection des cordes à vides avec un rond non jouées avec une croix
3. Nom de l'accord choisi
4. Sélection du choix entre plusieurs noms d'accord possibles
5. Notation cases
6. Notation résultante dans le format define
7. Ajout de l'accord dans la base


### Utilisation de la souris

- Par un click sur le bouton gauche de la souris on sélectionne
   - soit une corde entre deux fret
   - soit une corde à vide en cliquant en haut du manche
- Par un click sur le bouton droit on sélectionne la même fret appuyée
toutes les cordes afin de pouvoir définir des barrés
- Par l'utilisation de la molette de la souris on monte ou baisse les
cordes appuyées.

### Gestion des accords 

![Gestion des accords ](./img/chordmanagement.png)

1. Ce sélecteur permet de choisir un accord, on peut également 
restreindre la liste des accords ou l'ordonner en utilisant les filtres
3 et 2
2. Les accords peuvent être triés suivant le nom de l'accord, le numéro 
de frette ou l'index qui est le numéro d'ordre de l'accord dans la base.
3. Le filtre permet de restreindre les accords présentés en choisissant
les premières lettres de l'accord en langue anglaise. La petite croix
jouxtant la line d'édition permet d'effacer le nom de l'accord fugurant
dans le filtre.
4. Afficheur du nom de l'accord, si ce nom est modifié il peut être
sauvegardé. Mais attention le nom de l'accord doit être unique. On 
distinguera deux noms d'accords par l'emploin de parenthèses avec 
par exemple une notation en chiffres romains de la frette.
5. Afficheur du doigté de l'accord. Ce doigté peut être changé.
6. Bouton permettant de supprimer l'accord 
7. Bouton permettant de modifier l'accord courant avec les valeurs 
entrées dans les cases 4 et 5
8. Afficheur de l'accord.


### Mode approbation des accords

![Approbation des accords ](./img/chordapprovement.png)

Les accords peuvent être définis dans les fichiers de chansons par 
exemple par la directive 

~~~
{define: Eb95 base-fret 5 frets 5 6 6 5 6 x }
~~~

Un tel accord ca être automatiquement inclus dans la base, mais 
il sera nécessaire de l'approuver pour qu'il soit réellement 
opérationnel. 

1. Ce sélecteur permet de choisir un accord
2. La case montre le nom de l'accord. On peut copier ce nom 
mais pas le modifier 
3. La case montre le doigté de l'accord qui peut être copié mais non 
modifié.
4. L'accord peut être supprimé de la base, dans ce cas là il faut le
supprimé du fichier de chansons, sinon il sera inséré à nouveau.
5. L'accord peut être accepté dans la base
6. Cette zone permet de visualiser l'accord.


### Importation des accords

![Importation des accords ](./img/chordimport.png)

1. En copiant une liste d'accords, avec un accord par ligne, 
vous pouvez effectuer une importation de la base. Les accords devront
être sous la forme Nom=fret case case case case case case
2. Le bouton demandera l'importation effective

## Conversions

Les conversions sont obtenues par les sous menus du menu de conversions 
dans le menu outil :

![Menu conversion](./img/conversionmenu.png)

### Conversions accords sur 2 lignes vers chordpro

Ce mode permet de convertir des fichiers textes constitués par 
des accords au dessus des paroles : 

~~~
Sim 					 Fa#7
Elle est à toi cette chanson 
~~~

La conversion donnera le résultat suivant : 

~~~
[sim]Elle est à toi cette chan[Fa#7]son 
~~~

![Conversion format deux lignes vers chord](./img/twolineconversion.png)

1. Les fichiers étant généralement disponibles sur internet, le mode
opératoire choisi est de copier coller la chanson vers la zone
d'édition. Cela se fait par l'emploi des touches CTRL + C, CTRL + V
2. On peut choisir de convertir les accords et le symbole mineur. 
Dans l'exemple donné on peut choisir la langue des accords en anglais et
le symbole - pour le mode mineur, et les accords en français et le mode
mineur à -. Cela aura pour effet de concertir les accords de D- vers 
Rém.
3. Le mode mineur peut être ici - ou m 
4. La langue destination peut être choisie pour les accords
5. Le symbole mineur destination peut également être choisi
6. Le bouton Démonstration permet d'afficher une chanson à convertir
7. Efface la chanson en cours afin d'en copier une nouvelle
8. Lance la conversion dont le résultat est afficher en remplacement 
des donnés converties.

### Changer la langue des accords.

![Conversion de la langue des accords](./img/chordlanguageconversion.png)

1. Choisir la langue d'origine ( en général elle est positionnée
automatiquement)
2. Choisir la lettre pour signifier que l'accord dans la langue 
d'origine est mineur
3. Choisir la langue vers laquelle on souhaite convertir les noms d'accord
4. Choisir la lettre pour signifier que l'accord dans la langue à convertir
est mineur
5. Cliquer sur convertir

### Transposer les accords

![Transposer les accords](./img/transpose.png)

1. La molette a la même action que la zone d'entrée 2, elle permet de définir
le nombre de demi-tons positif ou négatif dont on veut transposer l'accord.
2. La zone d'entrée permet de définir
le nombre de demi-tons positif ou négatif dont on veut transposer l'accord.
3. On peut transposer l'accord sur l'accord sous la souris, sur toute la ligne
courante, sur la chanson courante ou sur tout le fichier
4. Ferme la boite de dialogue
5. Transpose l'accord

## Lancer l'afficheur PDF 

ChordV lance l'afficheur PDF que vous avez positionné dans les préférences

Cette option est disponible dans le menu outils

## Construire les fichiers PDF 

La construction d'un fichier PDF est presque instantanée. Elle est 
intégrée au logiciel.

Cette option est disponible dans le menu outils

## Construire et afficher les fichiers PDF

Ce mode construit un fichier PDF et lance son affichage.

Cette option est disponible dans le menu outils

## Mode mémo

Pour entrer dans le mode mémo actionner le menu Fenêtres/Mode Aide mémoire

![Transposer les accords](./img/LyricsMonitoring.png)

1. On sélectionne la chanson, ce qui présuppose qu'une chanson soit
ouverte
2. On peut modifier les valeurs qui sont par défaut positionnées aux
valeurs par défaut définie dans le menu Outils/Préférence
3. On lance le monitoring par le bouton 3
4. La touche ESCAPE permet de quitter le monitoring, la barre d'espace 
d'activer la pause ou de quitter la pause.

# Partie technique

## Raccourcis claviers - Actions souris 

### Raccourcis clavier 

-------------------------------------------------------------
 Raccourcis        Action       Raccourcis     Action         
------------ ---------------  ------------  -----------------
  CTRL + F    Rechercher        F1          Documentation   
  
  CTRL + O    Préférences       F2                          
  
  CTRL + R    Remplacer         F3          Déf. accords    
  
  CTRL + S    Sauvegarder       F4          Insert. accords 
  
  CTRL + +    Zoomer +          F5          PDF texte       
  
  CTRL + -    Zommer -          F6          PDF accord+text 
    
  CTRL + -    Zommer -          F7          PDF grille      
  
-------------------------------------------------------------
: Les raccourcis clavier


## Traduction du logiciel dans une langue

### Présentation

 Vous n'avez pas besoin des codes sources pour traduire le logiciel.
 Si vous vous rendez dans le menu système de l'application via 
Aide/Informations Systèmes, vous
trouverez le chemin des fichiers langues par exemple :

~~~bash
/home/gilles/.config/ChordV/ChordV.conf
~~~
- Dans le répertoire /home/gilles/.config/ChordV/ se trouvent les fichiers
de langue organisés dans le répertoire Languages contenant les langues
écrites avec le nom dans la langue traduite. Pour le français on trouvera
le nom avec la cédille exactement comme un français pourrait le lire.
- À l'intérieur du répertore Français on retrouve trois fichiers
    - fr.png : ce fichier est un drapeau de la langue au format png
    - fr.ts : ce fichier est le ficher contenant les paires de traduction
    - fr.qm  : ce fichier contient le fichier ts compilé
    - fr.html : la documentation en langue française dans le format HTML
    - fr.md : la documentation en langue en française dans le format md
    - fr.chords : contient la liste noms de note dans la langue, avec une note
    pour chaque ligne. La dernière ligne contient la liste des
    symboles utilisés dans la langue pour le mode mineur séparés par des ,
    En français : m,-

### Traduction du fichier fr.ts

- Créer un répertoire de langue avec le nom par exemple Español
- Copier le fichier fr.png en es.pgn
- vous pouvez télécharger le programme linguist et ouvrir le fichier fr.png
- Dans linguiste sauvegarder le fichier es.ts et actionner le menu
Fichier/Publier le fichier ts.qm sera créé
- N'oubliez pas d'écrire à l'auteur du logiciel pour lui communiquer le
fichier es.ts afin qu'il soit inclu dans la prochaine distribution du logiciel


## La documentation utilisateur de Chord V

### Présentation 

La documentation est accessible dans le logiciel via le menu aide
à l'item Documentation.

Cette documentation a été transformée automatiquement à partir 
du format Markdown vers le HTML via le programme Pandoc.

Le fichier documentation se trouve dans le répertoire cité la partie
[Traduction du logiciel dans une langue](#traduction-du-logiciel-dans-une-langue)


### Processus de traduction 

Si vous désirez traduire la documentation du logiciel, il faut récupérer
le fichier md dans la langue désirée, le convertir via un traducteur
automatique et le corriger.

Prendre garde car les traducteur on tendance à transformer les codes 
md du style 

~~~md
![La fenêtre d'édition](./img/editor.png)
~~~

en 

~~~md
! [La fenêtre d'édition] (./img/editor.png)
~~~

Une fois le fichier traduit, vous pouvez le convertir en format html
via la commande (après avoir récupéré la feuille de style css sur 
le net)

~~~bash
pandoc --toc --ascii --smart -N --css=pandoc.css  --from=markdown --to=html --output=es.html es.md
~~~


### Les images

Les images sont à inclure dans le répertoire img du répertoire Langage/es,
elles sont issues de copies d'écran. Si vous utilisez gimp vous pouvez utiliser 
le plugin drawnumbers qui permet de produire les pastilles rouges.

Il est disponible à l'adresse 
[Draw-number](xhttp://www.gillesmaire.com/tiki-index.php?page=draw-numbers)

## Compatibilité Chordpro

### Introduction 

Chord V est conçu pour produire 4 types de documents en même temps
et certaines balises chord pro sont à vocation unique. Ainsi nous 
ne voulons peut être pas sortir le même format pour chacun des 
documents, sachant que les livrets de paroles sont peut-être destiné
à un fichier imprimé et les fichiers de grilles d'accord sont peut 
être destinés à des fichiers PDF pour une liseuse ou une tablette.

Chord lit les fichiers Chordpro et sait extraire de son format un 
fichier compatible chordPro.

Mais certaines balises ne sont pas utilisées car remplacées par 
l'interface graphique. 

### Compatibilité ChordPro 2ii

------------------------------------------------------------------------
ChordPro 2ii                                Chord V
------------------------------    --------------------------------------
{new_song}	{ns}	              	Lu mais remplacé par title

{title} {t}										X

{subtitle} {st}									X

{comment:text} {c:text} 						X

{comment_italic:text} {ci:text}					X

{comment_box:text}  {cb:text}					X

{start_of_chorus} {soc} 						X

{end_of_chorus} {eoc}							X

{start_of_tab} {sot} 						   nOn

{end_of_tab} {eot}							   nOn

{define ... }								  biEntot  

{textfont:fontname} {tf:fontname}		 InterfaCe graphique

{textsize:fontsize} {ts:fontsize}		 InterfaCe graphique

{chordfont:fontname} {cf:fontname}		 InterfaCe graphique

{chordsize:fontsize} {cs:fontsize}		 InterfaCe graphique

{no_grid} {ng}								   nOn

{grid} {g} 									   nOn

{titles:flush}								   nOn

{new_page} {np}								  biEntot

{new_physical_page} {npp}					   nOn

{columns:number} {col:number}				    X

{column_break} {colb}						    X

{pagesize:type}  {papersize:type}	     InterfaCe graphique

------------------------------------------------------------------------
::Liste des commandes chordpro 2ii

