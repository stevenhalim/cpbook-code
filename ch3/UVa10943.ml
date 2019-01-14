(* How do you add? *)

(* top-down *)

(* open Printf
 * open Scanf
 * 
 * let memo = Array.make_matrix 110 110 (-1)
 * 
 * let rec ways n k =
 *   if k = 1 then  (\* only can use 1 number to add up to N *\)
 *     1  (\* the answer is definitely 1, that number itself *\)
 *   else if memo.(n).(k) <> -1 then
 *     memo.(n).(k)
 *   else begin
 *     (\* if k > 1, we can choose one number from [0..n] to be one of the number and recursively compute the rest *\)
 *     let total_ways = ref 0 in
 *     for split = 0 to n do
 *       total_ways := (!total_ways + ways (n - split) (k - 1)) mod 1_000_000  (\* we just need the modulo 1M *\)
 *     done;
 *     memo.(n).(k) <- !total_ways;  (\* memoize them *\)
 *     memo.(n).(k)
 *   end
 * 
 * let () =
 *   try
 *     while true do
 *       let n, k = scanf "%d %d\n" (fun x y -> x, y) in
 *       if n = 0 && k = 0 then raise Exit;
 *       printf "%d\n" (ways n k)  (\* some recursion formula + top down DP *\)
 *     done
 *   with Exit -> () *)



(* bottom-up *)

open Printf
open Scanf

let () =
  let dp = Array.make_matrix 110 110 0 in

  for i = 0 to 100 do  (* these are the base cases *)
    dp.(i).(1) <- 1
  done;

  for j = 1 to 100 do  (* these three nested loops form the correct topological order *)
    for i = 0 to 100 do
      for split = 0 to 100 - i do
        dp.(i + split).(j + 1) <- (dp.(i + split).(j + 1) + dp.(i).(j)) mod 1_000_000
      done
    done
  done;

  try
    while true do
      let n, k = scanf "%d %d\n" (fun x y -> x, y) in
      if n = 0 && k = 0 then raise Exit;
      printf "%d\n" dp.(n).(k)
    done
  with Exit -> ()
