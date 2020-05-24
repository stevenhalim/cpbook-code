open Printf

let rec binary_search arr lo hi x =
	if lo = hi then false 
	else begin
		let mid = (lo + hi) / 2 in 
		if arr.(mid) = x then true
		else if arr.(mid) > x then (binary_search arr lo mid x)
		else binary_search arr (mid+1) hi x
	end


let () =
	let l = [| 10; 7; 5; 20; 8 |] in 
	Array.sort compare l;
	printf "%B\n" (binary_search l 0 5 7)
