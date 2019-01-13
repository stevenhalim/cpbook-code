open Printf
open Scanf

let max_gm = 30
let max_m = 210

let m = ref 0
let c = ref 0
let memo = Array.make_matrix max_gm max_m (-1)

let rec shop price g money =
  if money < 0 then -1
  else if g = !c then !m-money
  else if memo.(g).(money) <> -1 then memo.(g).(money)
  else
    let ans =
      price.(g)
      |> Array.map (fun p -> shop price (g+1) (money-p))
      |> Array.fold_left max (-1)
    in
    memo.(g).(money) <- ans;
    ans

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for _ = 1 to tc do
    scanf "%d %d\n" (fun x y -> m := x; c := y);
    let price = Array.init !c (fun _ ->
        scanf "%d " (fun k ->
            Array.init k (fun _ -> scanf "%d " (fun x -> x))))
    in
    let ans = shop price 0 !m in
    if ans < 0 then printf "no solution\n"
    else printf "%d\n" ans
  done
