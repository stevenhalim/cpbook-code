open Printf

let () =
	let a = (5, 24, -1982) in 
	let b = (5, 24, -1980) in 
	let c = (11, 13, -1983) in 
	let birthdays = [| a; b; c |] in 
	Array.sort compare birthdays;
	Array.iter (fun (m, d, y) ->
		printf "%d %d %d\n" d m (-y)
	) birthdays

