get_sorted(X) :-
	findall(Case-Name, cases(Name, Case), List),
	keysort(List, Pairs),
	pairs_values(Pairs, Sorted),
	X = Sorted.
