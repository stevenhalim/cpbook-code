open Scanf
open Printf

let () =
	scanf "%d\n" (fun x ->
		for i = 1 to x do 
			scanf "0.%[0-9]...\n" (fun s -> 
				printf "the digits are 0.%s\n" s
			)
		done
	)
