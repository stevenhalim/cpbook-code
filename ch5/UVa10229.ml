(* Modular Fibonacci *)

open Printf
open Scanf

let max_n = 2                                 (* increase this if needed *)
let mask = ref 0

let mat_id =                                  (* prepare identity matrix *)
  Array.init max_n @@ fun i ->
  Array.init max_n @@ fun j ->
  if i = j then 1 else 0

let mat_fib = [|                         (* special matrix for Fibonacci *)
  [|1; 1|];
  [|1; 0|]
|]

let mat_mul a b =                           (* O(n^3), but O(1) as n = 2 *)
  let ans = Array.make_matrix max_n max_n 0 in
  for i = 0 to max_n - 1 do
    for j = 0 to max_n - 1 do
      for k = 0 to max_n - 1 do
        ans.(i).(j) <- (ans.(i).(j) + a.(i).(k) * b.(k).(j)) land !mask
      done
    done
  done;
  ans

let mat_pow base p =              (* O(n^3 log p), but O(log p) as n = 2 *)
  let rec aux base p acc =
    if p = 0 then acc
    else
      let acc = if p land 1 = 1 then mat_mul acc base else acc in
      let base = mat_mul base base in                 (* square the base *)
      let p = p lsr 1 in                                (* divide p by 2 *)
      aux base p acc
  in
  aux base p mat_id

let () =
  try
    while true do
      let n, m = scanf "%d %d\n" (fun x y -> x, y) in
      mask := 1 lsl m - 1;
      let ans = mat_pow mat_fib n in                         (* O(log n) *)
      printf "%d\n" ans.(0).(1)
    done
  with End_of_file -> ()
