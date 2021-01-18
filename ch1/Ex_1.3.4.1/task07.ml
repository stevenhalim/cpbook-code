open Printf

let remove_from x l = List.filter ((<>) x) l

let rec permutations = function  
  | [] -> []
  | x::[] -> [[x]]
  | xs -> 
    List.fold_left (fun acc x -> acc @ List.map (fun perm -> x::perm) (permutations (remove_from x xs))) [] xs

let print xs =
	List.iter (fun x -> printf "%c " x) xs;
	printf "\n"

let () =
	let open Char in 
	let p = List.init 4 (fun x -> chr (code 'A' + x)) in (* change 4 to 10 to match the actual problem (but it will take some time to print) *)
	List.iter print (permutations p)
