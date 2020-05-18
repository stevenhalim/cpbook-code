 (* World Finals Stockholm 2009, A - A Careful Approach, UVa 1079, LA 4445 *)

open Scanf
open Printf


let order = Array.make 8 0
let a = Array.make 8 0.
let b = Array.make 8 0.
let case = ref 0

let remove_from x l = List.filter ((<>) x) l

let rec get_permutations = function  
  | [] -> []
  | x::[] -> [[x]]
  | xs -> 
    List.fold_left (fun acc x -> acc @ List.map (fun perm -> x::perm) (get_permutations (remove_from x xs))) [] xs

let load_perm xs =
	let rec helper idx = function
		| [] -> ()
		| hd :: tl -> (
			order.(idx) <- hd;
			helper (idx+1) tl
		)
	in
	helper 0 xs


let solve n =
	for i = 0 to n-1 do
		scanf "%f %f\n" (fun x y ->
			a.(i) <- 60. *. x;
			b.(i) <- 60. *. y
		)
	done;
	let maxL = ref (-1.) in
	let perms = get_permutations (List.init n (fun x -> x)) in
	let greedy_landing l =
		let last_landing = ref a.(order.(0)) in
		let rec helper i =
			if i = n then !last_landing -. b.(order.(n-1))
			else if Float.compare (!last_landing +. l) b.(order.(i)) > 0 then 1.
			else begin
				last_landing := max a.(order.(i)) (!last_landing +. l);
				helper (i+1)
			end
		in
		helper 1
	in
	let bSearch () =
		let lo = ref 0. and hi = ref 86400. in
		while compare (Float.abs (!lo -. !hi)) 0.001 >= 0 do 
			let l = (!lo +. !hi) /. 2. in
			let retVal = greedy_landing l in
			if compare retVal 0.01 <= 0 then lo := l else hi := l
		done;
		maxL := max !maxL !hi
	in
	List.iter (fun perm -> load_perm perm; bSearch ()) perms;
	let secs = Float.to_int (!maxL +. 0.5) in
	incr case;
	printf "Case %d: %d:%0.2d\n" !case (secs/60) (secs mod 60)


let () =
	let rec loop () = 
		scanf "%d\n" (fun n ->
			if n <> 0 then begin
				solve n;
				loop ()
			end
		)
	in
	loop ()
