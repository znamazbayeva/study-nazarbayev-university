dist(X, Y, Z) :-  
	(
		(Y - X) =< 0, Z is (X - Y), !;
		(Y - X) > 0, Z is (Y - X)
	).

canstrike( q( X1, Y1 ), q( X2, Y2 ) ) :- 
	(
		X1 =:= X2;
		Y1 =:= Y2;
		dist(X1, X2, Z1),
		dist(Y1, Y2, Z2),
		Z1 =:= Z2
	).

betw(L, U, X) :- L =< U, X = L.
betw(L, U, X) :- L < U,  L1 is L+1, betw(L1, U, X).

cannotstrike( [], _).
cannotstrike( [D|L], q(X,Y) ) :-
	(
		not(canstrike(D, q(X, Y))),
		cannotstrike(L, q(X, Y))
	).

queens( 0, N, P1, P2 ) :- P2 = P1.
queens( I, N, P1, P2 ) :- 
(
	I > 0, 
	I1 is I - 1,
	betw(1, N, X), betw(1, N, Y),
	cannotstrike( P1, q(X, Y)), P_N = [q(X, Y) | P1],
	queens( I1, N, P_N , P2)
	).