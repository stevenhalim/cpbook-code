(* Pseudo-Random Numbers *)
open Scanf
open Printf

let z = ref 0
let i = ref 0
let m = ref 0

let f x = (!z * x + !i) mod !m

let floydCycleFinding x0 = (* function int f(int x) is defined earlier *)
  (* 1st part: finding k*mu, hare's speed is 2x tortoise's *)
  let tortoise = ref (f x0) and hare = ref (f (f x0)) in
  while !tortoise <> !hare do
    tortoise := f !tortoise;
    hare := f (f !hare)
  done;
  (* 2nd part: finding mu, hare and tortoise move at the same speed *)
  let mu = ref 0 in
  hare := x0;
  while !tortoise <> !hare do 
    tortoise := f !tortoise;
    hare := f !hare;
    incr mu 
  done;
  (* 3rd part: finding lambda, hare moves, tortoise stays *)
  let lambda = ref 1 in
  hare := f !tortoise;
  while !tortoise <> !hare do 
    hare := f !hare;
    incr lambda
  done;
  (!mu, !lambda)

let () =
  let case = ref 1 in
  let rec solve () =
    scanf "%d %d %d %d" (fun zz ii mm l ->
      if zz lor ii lor mm lor l > 0 then begin
        z := zz; i := ii; m := mm;
        let (_, ans) = floydCycleFinding l in
        printf "Case %d: %d\n" !case ans;
        incr case;
        scanf "\n" ();
        solve ()
      end
    )
  in
  solve ()

