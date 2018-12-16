open Printf

let ls_one s = s land (-s)

let rec ctz x =
	let rec helper num ans = 
		if num land 1 = 1 then ans
	 	else helper (num lsr 1) (ans+1)
	 in 
	 helper x 0

let () =
	let n = 20 in
	for i = 0 to (1 lsl n) - 1 do 
		let pos = ref i in 
		while !pos > 0 do
			let ls = ls_one !pos in 
			pos := !pos - ls;
			printf "%d " (ctz ls)
		done;
		printf "\n"
	done