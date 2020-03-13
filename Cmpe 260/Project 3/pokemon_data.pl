% pokemon_stats(Pokemon, Types, HealthPoint, Attack, Defense).
pokemon_stats(bulbasaur, [grass, poison], 45, 49, 49).
pokemon_stats(ivysaur, [grass, poison], 60, 62, 63).
pokemon_stats(venusaur, [grass, poison], 80, 100, 123).
pokemon_stats(charmander, [fire], 39, 52, 43).
pokemon_stats(charmeleon, [fire], 58, 64, 58).
pokemon_stats(charizard, [fire, flying], 78, 104, 78).
pokemon_stats(squirtle, [water], 44, 48, 65).
pokemon_stats(wartortle, [water], 59, 63, 80).
pokemon_stats(blastoise, [water], 79, 103, 120).
pokemon_stats(caterpie, [bug], 45, 30, 35).
pokemon_stats(metapod, [bug], 50, 20, 55).
pokemon_stats(butterfree, [bug, flying], 60, 45, 50).
pokemon_stats(pidgey, [normal, flying], 40, 45, 40).
pokemon_stats(pidgeotto, [normal, flying], 63, 60, 55).
pokemon_stats(pidgeot, [normal, flying], 83, 80, 80).
pokemon_stats(ekans, [poison], 35, 60, 44).
pokemon_stats(arbok, [poison], 60, 95, 69).
pokemon_stats(pikachu, [electric], 35, 55, 40).
pokemon_stats(raichu, [electric], 60, 85, 50).
pokemon_stats(vulpix, [fire, ice], 38, 41, 40).
pokemon_stats(ninetales, [fire, ice], 73, 67, 75).
pokemon_stats(jigglypuff, [normal, fairy], 115, 45, 20).
pokemon_stats(wigglytuff, [normal, fairy], 140, 70, 45).
pokemon_stats(zubat, [poison, flying], 40, 45, 35).
pokemon_stats(golbat, [poison, flying], 75, 80, 70).
pokemon_stats(meowth, [normal, dark], 40, 35, 35).
pokemon_stats(persian, [normal, dark], 65, 60, 60).
pokemon_stats(psyduck, [water], 50, 52, 48).
pokemon_stats(golduck, [water], 80, 82, 78).
pokemon_stats(abra, [psychic], 25, 20, 15).
pokemon_stats(kadabra, [psychic], 40, 35, 30).
pokemon_stats(alakazam, [psychic], 55, 50, 65).
pokemon_stats(machop, [fighting], 70, 80, 50).
pokemon_stats(machoke, [fighting], 80, 100, 70).
pokemon_stats(machamp, [fighting], 90, 130, 80).
pokemon_stats(geodude, [rock, ground], 40, 80, 100).
pokemon_stats(graveler, [rock, ground], 55, 95, 115).
pokemon_stats(golem, [rock, ground], 80, 120, 130).
pokemon_stats(grimer, [poison], 80, 80, 50).
pokemon_stats(muk, [poison], 105, 105, 75).
pokemon_stats(shellder, [water], 30, 65, 100).
pokemon_stats(cloyster, [water, ice], 50, 95, 180).
pokemon_stats(gastly, [ghost, poison], 30, 35, 30).
pokemon_stats(haunter, [ghost, poison], 45, 50, 45).
pokemon_stats(gengar, [ghost, poison], 60, 65, 80).
pokemon_stats(onix, [rock, ground], 35, 45, 160).
pokemon_stats(drowzee, [psychic], 60, 48, 45).
pokemon_stats(hypno, [psychic], 85, 73, 70).
pokemon_stats(exeggcute, [grass, psychic], 60, 40, 80).
pokemon_stats(exeggutor, [grass, psychic], 95, 105, 85).
pokemon_stats(lickitung, [normal], 90, 55, 75).
pokemon_stats(koffing, [poison], 40, 65, 95).
pokemon_stats(weezing, [poison], 65, 90, 120).
pokemon_stats(horsea, [water], 30, 40, 70).
pokemon_stats(seadra, [water], 55, 65, 95).
pokemon_stats(staryu, [water], 30, 45, 55).
pokemon_stats(starmie, [water, psychic], 60, 75, 85).
pokemon_stats(magmar, [fire], 65, 95, 57).
pokemon_stats(magikarp, [water], 20, 10, 55).
pokemon_stats(gyarados, [water, flying], 95, 155, 109).
pokemon_stats(lapras, [water, ice], 130, 85, 80).
pokemon_stats(eevee, [normal], 55, 55, 50).
pokemon_stats(articuno, [ice, flying], 90, 85, 100).
pokemon_stats(zapdos, [electric, flying], 90, 90, 85).
pokemon_stats(moltres, [fire, flying], 90, 100, 90).
pokemon_stats(dratini, [dragon], 41, 64, 45).
pokemon_stats(dragonair, [dragon], 61, 84, 65).
pokemon_stats(dragonite, [dragon, flying], 91, 134, 95).
pokemon_stats(mewtwo, [psychic], 106, 150, 70).
pokemon_stats(mew, [psychic], 100, 100, 100).


% pokemon_evolution(Pokemon, EvolvedPokemon, MinRequiredLevel).
pokemon_evolution(bulbasaur, ivysaur, 16).
pokemon_evolution(ivysaur, venusaur, 32).
pokemon_evolution(charmander, charmeleon, 16).
pokemon_evolution(charmeleon, charizard, 36).
pokemon_evolution(squirtle, wartortle, 16).
pokemon_evolution(wartortle, blastoise, 36).
pokemon_evolution(caterpie, metapod, 7).
pokemon_evolution(metapod, butterfree, 10).
pokemon_evolution(pidgey, pidgeotto, 18).
pokemon_evolution(pidgeotto, pidgeot, 36).
pokemon_evolution(ekans, arbok, 22).
pokemon_evolution(zubat, golbat, 22).
pokemon_evolution(meowth, persian, 28).
pokemon_evolution(psyduck, golduck, 33).
pokemon_evolution(abra, kadabra, 16).
pokemon_evolution(machop, machoke, 28).
pokemon_evolution(geodude, graveler, 25).
pokemon_evolution(grimer, muk, 38).
pokemon_evolution(gastly, haunter, 25).
pokemon_evolution(drowzee, hypno, 26).
pokemon_evolution(koffing, weezing, 35).
pokemon_evolution(horsea, seadra, 32).
pokemon_evolution(magikarp, gyarados, 20).
pokemon_evolution(dratini, dragonair, 30).
pokemon_evolution(dragonair, dragonite, 55).



% pokemon_types(PokemonTypes).
pokemon_types([normal, fire, water, electric, grass, ice, fighting, poison, ground, flying, psychic, bug, rock, ghost, dragon, dark, steel, fairy]).

% type_chart_attack(AttackingType, TypeMultipliers).
type_chart_attack(normal, [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0]).
type_chart_attack(fire, [1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0]).
type_chart_attack(water, [1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0]).
type_chart_attack(electric, [1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0]).
type_chart_attack(grass, [1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0]).
type_chart_attack(ice, [1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0]).
type_chart_attack(fighting, [2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5]).
type_chart_attack(poison, [1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0]).
type_chart_attack(ground, [1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0]).
type_chart_attack(flying, [1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0]).
type_chart_attack(psychic, [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0]).
type_chart_attack(bug, [1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5]).
type_chart_attack(rock, [1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0]).
type_chart_attack(ghost, [0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0]).
type_chart_attack(dragon, [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0]).
type_chart_attack(dark, [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5]).
type_chart_attack(steel, [1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0]).
type_chart_attack(fairy, [1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0]).


% pokemon_trainer(PokemonTrainer, PokemonTeam, PokemonLevels)
pokemon_trainer(ash, [pikachu, ivysaur, charmeleon, squirtle], [45, 15, 28, 50]).
pokemon_trainer(misty, [psyduck, staryu, starmie, seadra], [10, 15, 48, 45]).
pokemon_trainer(brock, [onix, geodude, golbat, machop], [18, 33, 42, 33]).
pokemon_trainer(team_rocket, [meowth, ekans, gyarados, weezing], [15, 30, 29, 35]).



find_pokemon_evolution(PokemonLevel, Pokemon, EvolvedPokemon) :-
	(pokemon_evolution(Pokemon, X, Rq1), PokemonLevel >= Rq1, find_pokemon_evolution(PokemonLevel, X, EvolvedPokemon))
	;(EvolvedPokemon = Pokemon).

% finds all pokemon evolves

pokemon_level_stats(PokemonLevel, Pokemon, PokemonHp, PokemonAttack, PokemonDefense) :-
	pokemon_stats(Pokemon, _, HealthPoint, Attack, Defense), (PokemonHp is PokemonLevel * 2 + HealthPoint),
	 (PokemonAttack is PokemonLevel + Attack), (PokemonDefense is PokemonLevel + Defense).

% finds all pokemon health, attack and defense point


single_type_multiplier(AttackerType, DefenderType, Multiplier) :-	 
	type_chart_attack(AttackerType, AttackingList), pokemon_types(PokemonTypes),
	stm1(AttackingList, PokemonTypes, DefenderType, Multiplier).


% finds all pokemon multipliers or pokemon types in order to 
% pokemon types that are given or


stm1([H1|List1], [H2|List2], D, M) :-
	((D = H2, M is H1); stm1(List1, List2, D, M)).

% works as a helper for single_type_multiplier

type_multiplier(AttackerType, DefenderTypeList, Multiplier) :-
	pokemon_types(PokemonTypes), (A is 1),
	tm1(AttackerType, DefenderTypeList, Multiplier, A).

% finds pokemon types or multipliers for defender type

tm1(_,[], M, M).	

tm1(Atc, [H|List], M, A) :-
	type_chart_attack(Atc, AtcList),
	single_type_multiplier(Atc, H, Temp), (K is A * Temp),
	tm1(Atc, List, M, K).

% works as a helper for type_multiplier


pokemon_type_multiplier(AttackerPokemon, DefenderPokemon, Multiplier) :-
	pokemon_stats(AttackerPokemon, AtcTypeList, _, _, _), 
	pokemon_stats(DefenderPokemon, DefTypeList, _, _, _), 
	(A is 0), ptm1(AtcTypeList, DefTypeList, Multiplier, A).
	
% finds pokemons or multipliers for given in the function

ptm1([], _, M, M).

ptm1([H1|List1], List2, M, A) :-
	type_multiplier(H1, List2, K),
	((K >= A, ptm1(List1, List2, M, K)); (A > K, ptm1(List1, List2, M, A))).

% works as a helper for pokemon_type_multiplier


pokemon_attack(AttackerPokemon, AttackerPokemonLevel, DefenderPokemon, DefenderPokemonLevel, Damage) :-
	pokemon_level_stats(AttackerPokemonLevel, AttackerPokemon, _, AtcPokemonAttack, _),
	pokemon_level_stats(DefenderPokemonLevel, DefenderPokemon, _, _, DefPokemonDefense),
	pokemon_type_multiplier(AttackerPokemon, DefenderPokemon, Multiplier),
	(Damage is (0.5 * AttackerPokemonLevel * (AtcPokemonAttack / DefPokemonDefense) * Multiplier) + 1), !.

% calculates damages for attacker and defender pokemon


pokemon_fight(Pokemon1, Pokemon1Level, Pokemon2, Pokemon2Level, Pokemon1Hp, Pokemon2Hp, Rounds) :-
	pokemon_level_stats(Pokemon1Level, Pokemon1, Hp1, Atc1, Def1),
	pokemon_level_stats(Pokemon2Level, Pokemon2, Hp2, Atc2, Def2),
	pokemon_attack(Pokemon1, Pokemon1Level, Pokemon2, Pokemon2Level, Damage1),
	pokemon_attack(Pokemon2, Pokemon2Level, Pokemon1, Pokemon1Level, Damage2),
	(A is 1), pf1(Hp1, Hp2, Damage1, Damage2, A, Pt1, Pt2, ATemp),
	(Pokemon1Hp is Pt1 - Damage2), (Pokemon2Hp is Pt2 - Damage1), (Rounds is ATemp),!.

% calculates pokemons hps and rounds for given pokemons in the fight
	
pf1(Hp1, Hp2, Damage1, Damage2, A, Pokemon1Temp, Pokemon2Temp, ATemp) :-
	(NewHp1 is Hp1 - Damage2), (NewHp2 is Hp2 - Damage1), (K is A + 1),
	(((NewHp1 > 0), (NewHp2 > 0)), pf1(NewHp1, NewHp2, Damage1, Damage2, K, Pokemon1Temp, Pokemon2Temp, ATemp));
	(Pokemon1Temp is Hp1, Pokemon2Temp is Hp2, ATemp is A, !).

% works as a helper for pokemon_fight

pokemon_tournament(PokemonTrainer1, PokemonTrainer2, WinnerTrainerList) :-
	pokemon_trainer(PokemonTrainer1, PokemonTeam1, PokemonLevels1),
	pokemon_trainer(PokemonTrainer2, PokemonTeam2, PokemonLevels2),
	tour1(PokemonTeam1, PokemonTeam2, PokemonLevels1, PokemonLevels2, PokemonTrainer1, PokemonTrainer2, WinnerTrainerList), !.

% gives a winner list in the pokemon tournement

tour1([], [], [], [], _, _, []).

tour1([P1|Team1], [P2|Team2], [L1|Level1], [L2|Level2], T1, T2, [W|Win]) :-
	find_pokemon_evolution(L1, P1, E1),
	find_pokemon_evolution(L2, P2, E2),
	pokemon_fight(E1, L1, E2, L2, Hp1, Hp2, _),	
	((Hp1 >= Hp2, W = T1); (Hp2 > Hp1, W = T2)), tour1(Team1, Team2, Level1, Level2, T1, T2, Win).

% works as a helper for pokemon_tournament

allPokemonList(Pokes) :-
	findall(Pokemon, pokemon_stats(Pokemon, _, _, _, _), Pokes).

% finds all pokemons


best_pokemon(EnemyPokemon, LevelCap, RemainingHP, BestPokemon) :-
	allPokemonList([P|Pokes]), pokemon_fight(P, LevelCap, EnemyPokemon, LevelCap, T, _, _),
	bp(EnemyPokemon, LevelCap, Pokes, TempHp, TemPo, P, T),
	(RemainingHP is TempHp), (BestPokemon = TemPo).

% finds the best pokemon for a specific pokemon as a rival.

bp(_, _, [], H, P, P, H).


bp(Enemy, LevelCap, [H|List], TempHp, TemPo, P, T) :-
	pokemon_fight(H, LevelCap, Enemy, LevelCap, Hp1, _, _),
	((Hp1 >= T, bp(Enemy, LevelCap, List, TempHp, TemPo, H, Hp1))
	;(T > Hp1, bp(Enemy, LevelCap, List, TempHp, TemPo, P, T))).

% works as a helper best_pokemon

best_pokemon_team(Trainer, PokemonTeam) :-
	pokemon_trainer(Trainer, Team, LevelList),
	bpt(Team, LevelList, PokemonTeam).

% finds the best team against a specific team

bpt([], [], []).

bpt([T|Team], [L|List], [B|BestTeam]) :-
	best_pokemon(T, L, _, B),
	bpt(Team, List, BestTeam), !.

% works as a helper best_pokemon_team

pokemon_types(TypeList, InitialPokemonList, PokemonList) :-
	findall(Pokemon, (member(Pokemon, InitialPokemonList), pt1(TypeList, Pokemon)), PokemonList).

% gives a common list for function

pt1([H|TypeList], Pokemon) :-
	pokemon_stats(Pokemon, PokemonList, _,_,_),
	((member(H, PokemonList), !); pt1(TypeList, Pokemon)).

% works as a helper for pokemon_types


generate_pokemon_team(LikedTypes, DislikedTypes, Criterion, Count, PokemonTeam) :-
	allPokemonList(Pokes), pokemon_types(LikedTypes, Pokes, LikedList),
	pokemon_types(DislikedTypes, Pokes, DislikedList),
	findall(Pokemon, (member(Pokemon, LikedList), \+member(Pokemon, DislikedList)), PokemonList),
	quick_sort2(PokemonList, Sorted, Criterion),
	(A is 0), gpt1(Sorted, PokemonTeam, Count, A).

% finds all pokemons
% finds liked types list
% finds disliked types list
% finds pokemons have liked types and does not have disliked types
% finds sorted list for criterion
% gives a ranked pokemon list for criterion, liked and disliked types


gpt1(_, [], C, C).

gpt1([S|Sorted], [T|Team], C, A) :-
	pokemon_stats(S, _, Hp, Atc, Def),
	(T = [S, Hp, Atc, Def]), (K is A + 1),
	gpt1(Sorted, Team, C, K), !.

% works as a helper for generate_pokemon_team
	

quick_sort2(List, Sorted, C):-
	q_sort(List, [], Sorted, C).

q_sort([],Acc,Acc, _).

q_sort([H|T], Acc, Sorted, C) :-
	pivoting(H,T,L1,L2, C),
	q_sort(L1,Acc,Sorted1, C), 
	q_sort(L2,[H|Sorted1],Sorted, C), !.
   
pivoting(_,[],[],[], _).

pivoting(H,[X|T],[X|L],G, C):- 
	pokemon_stats(H, _, HH, HA, HD),
	pokemon_stats(X, _, XH, XA, XD),
	(((C == h, HH >= XH); (C == a, HA >= XA);
	(C == d, HD >= XD)), pivoting(H,T,L,G,C)), !.

pivoting(H,[X|T],L,[X|G], C):- 
	pokemon_stats(H, _, HH, HA, HD),
	pokemon_stats(X, _, XH, XA, XD),
	(((C == h, XH > HH); (C == a, XA > HA);
	(C == d, XD > HD)), pivoting(H,T,L,G,C)), !.


% quick sorting algorithm
