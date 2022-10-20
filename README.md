# BomberMan
Indie Studio Epitech Lille - Intelligence Artificielle

Le binaire pour lancer le jeu est "bomberman" fonctionnant sous Linux, j'ai développé l'intelligence Artificielle de l'Indie Studio avec l'aide de A* pour le pathfinding.

Les participants au projet sont:
Pierres-Jean Descarpenteries - ECS
Matthias Petitjean - Engine
Quentin Dubois - Gameplay
Thibaud Fontaine - Sound Design & Modèles
Rayan Benguedih - Intelligence Artificielle


Fonctionnement de l'IA:

Prévilégie sa survie en regardant les bombes autour
Récupère les power ups pour s'améliorer
Casse les caisses destructibles pour s'améliorer
Tue le joueur et le pourchasse



Bugs connus:
Protocole 3 - (L'IA tente d'aller hors map et se suicide)
L'Intelligence artificielle, en plein milieu de son chemin, va éviter une bombe, pour reprendre sa route, cause du bug: Vérification de danger en plein chemin
Fix prévus: Modifier A* pour rendre le chemin passant par les bombes plus coûteux + Update la route

Promo 2025


Indie Studio Epitech Lille - Artificial Intelligence
The binary to start the game is "bomberman" working under Linux I developped the Artificial Intelligence of the project using A* for the pathfinding and elaborating my own algorithm for the behavioral of the AI 

Participants:
Pierres-Jean Descarpenteries - ECS
Matthias Petitjean - Engine
Quentin Dubois - Gameplay
Thibaud Fontaine - Sound Design & Models
Rayan Benguedih - Artificial Intelligence

What the AI does:
Puts survival above all
Picks up power ups to improve itself
Destroys breakable cases
Kills and chases the player

Known bugs:
Protocole 3 - (The AI kills itself trying to go out of map, due to threads unknown reason yet)
The AI might bug trying to avoid a bomb while trying to reach a power up, it will cancel it's path to avoid to be on the bomb's way, then reset it's action, the A* implementation hasn't taken into acount the weight of the bomb's path just yet

