open Printf

(* returns a list containing the unique elements of a sorted array *)
let unique arr =
	Array.fold_right (fun elem xs ->
			if xs = [] || not (elem = List.hd xs) then elem :: xs else xs
		) arr []

let () =
	let v = [| 1; 2; 2; 2; 3; 3; 2; 2; 1 |] in 
	Array.sort compare v;
	List.iter (fun x -> printf "%d\n" x)  (unique v)