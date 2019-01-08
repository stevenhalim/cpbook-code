(* ACORN *)

open Scanf
open Printf

let solve t h f =
	let acorn = Array.init 2010 (fun _ -> Array.make 2010 0) in
	for i = 0 to t-1 do 
		scanf "%d" (fun a ->
			for j = 1 to a do 
				scanf " %d" (fun n -> acorn.(i).(n) <- acorn.(i).(n) + 1)
			done
		);
		scanf "\n" ()
	done;
	let dp = Array.make 2010 0 in
	for tree = 0 to t-1 do dp.(h) <- max dp.(h) acorn.(tree).(h) done;
	for height = h-1 downto 0 do 
		for tree = 0 to t-1 do 
			acorn.(tree).(height) <-
				acorn.(tree).(height) + 
				max acorn.(tree).(height+1) (if height + f <= h then dp.(height+f) else 0);
			dp.(height) <- max dp.(height) acorn.(tree).(height)
		done
	done;
	printf "%d\n" dp.(0)

let () =
	scanf "%d\n" (fun c ->
		for case = 1 to c do 
			scanf "%d %d %d\n" solve
		done
	)
