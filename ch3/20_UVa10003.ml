(* Cutting Sticks *)
(* Top-Down DP *)

open Printf
open Scanf

let a = Array.make 55 0
let memo = Array.make_matrix 55 55 (-1)

let rec cut left right =
  if left + 1 = right then 0
  else if memo.(left).(right) <> -1 then memo.(left).(right)
  else begin
    let ans = ref 2_000_000_000 in
    for i = left + 1 to right - 1 do
      ans := min !ans (cut left i + cut i right + a.(right) - a.(left))
    done;
    memo.(left).(right) <- !ans;
    memo.(left).(right)
  end

let () =
  try
    while true do
      let l = scanf "%d\n" (fun x -> x) in
      if l = 0 then raise Exit;
      let n = scanf "%d\n" (fun x -> x) in
      for i = 1 to n do
        a.(i) <- scanf "%d " (fun x -> x)
      done;
      a.(n + 1) <- l;

      Array.iter (fun a -> Array.fill a 0 (Array.length a) (-1)) memo;
      printf "The minimum cutting is %d.\n" (cut 0 (n + 1))  (* start with left = 0 and right = n + 1 *)
    done
  with Exit -> ()
