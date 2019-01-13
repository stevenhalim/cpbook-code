open Printf
open Scanf

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for _ = 1 to tc do
    let target = scanf "%d\n" (fun x -> x) in
    let n = scanf "%d\n" (fun x -> x) in
    let l = Array.init n (fun i -> scanf "%d " (fun x -> x)) in
    try
      for mask = 0 to 1 lsl n - 1 do
        let sum =
          List.init n (fun j -> if mask land 1 lsl j <> 0 then l.(j) else 0)
          |> List.fold_left (+) 0
        in
        if sum = target then raise Exit
      done;
      printf "NO\n"
    with Exit ->
      printf "YES\n"
  done
