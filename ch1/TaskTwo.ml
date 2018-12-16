open Scanf
open Printf

let () = 
	let pi = 2. *. acos 0. in 
	scanf "%d" (fun n -> printf "%.*f\n" n pi)
