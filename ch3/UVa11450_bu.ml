open Printf
open Scanf

let max_gm = 30
let max_m = 210

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for _ = 1 to tc do
    let m, c = scanf "%d %d\n" (fun x y -> x, y) in
    let price = Array.init c (fun _ ->
        scanf "%d " (fun k ->
            Array.init k (fun _ -> scanf "%d " (fun x -> x))))
    in

    let reachable = Array.make_matrix 2 (m+1) false in
    price.(0) |> Array.iter (fun p ->
        if m-p >= 0 then reachable.(0).(m-p) <- true
      );

    let cur = ref 1 in
    for g = 1 to c-1 do
      Array.fill reachable.(!cur) 0 (Array.length reachable.(!cur)) false;
      for money = 0 to m-1 do
        if reachable.(1 - !cur).(money) then
          price.(g) |> Array.iter (fun p ->
              if money-p >= 0 then
                reachable.(!cur).(money-p) <- true
            )
      done;
      cur := 1 - !cur
    done;

    let money = ref 0 in
    while !money <= m && not reachable.(1 - !cur).(!money) do
      money := !money+1
    done;

    if !money = m+1 then printf "no solution\n"
    else printf "%d\n" (m - !money)
  done
