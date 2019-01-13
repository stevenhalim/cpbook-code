(* Coin Change *)

open Printf
open Scanf

let n = 5
let coin_value = [|1; 5; 10; 25; 50|]
let memo = Array.make_matrix 6 7500 (-1)  (* we only need to initialize this once *)
(* n and coin_value are fixed for this problem, max v is 7489 *)

let rec ways typ value =
  if value = 0 then 1
  else if value < 0 || typ = n then 0
  else if memo.(typ).(value) <> -1 then memo.(typ).(value)
  else begin
    memo.(typ).(value) <- ways (typ + 1) value + ways typ (value - coin_value.(typ));
    memo.(typ).(value)
  end

let () =
  try
    while true do
      let v = scanf "%d\n" (fun x -> x) in
      printf "%d\n" (ways 0 v)
    done
  with
    End_of_file -> ()
