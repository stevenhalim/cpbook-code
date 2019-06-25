open Printf
open Scanf

let eps = 1e-9

type event =
  | Fuel of float
  | Leak
  | Gas_station
  | Mechanic
  | Goal

let rec binsearch can lo hi =
  if hi-.lo < eps then
    hi
  else
    let mid = (lo+.hi) /. 2.0 in
    if can mid then
      binsearch can lo mid
    else
      binsearch can mid hi

let rec read_events () =
  let d, line = scanf "%f %[^\n]\n" (fun x y -> x, y) in
  let e = match line with
    | "Leak" -> Leak
    | "Gas station" -> Gas_station
    | "Mechanic" -> Mechanic
    | "Goal" -> Goal
    | _ ->
      let n = sscanf line "Fuel consumption %f" (fun x -> x) in
      if n = 0.0 then raise Exit
      else Fuel n
  in
  (d, e) :: match e with
  | Goal -> []
  | _ -> read_events ()

let can_events events original_f =
  let f = ref original_f in
  let cur_d = ref 0.0 in
  let cur_n = ref 0.0 in
  let leak_rate = ref 0.0 in
  let rec go = function
    | [] -> true
    | (d, e) :: events' ->
      let dt = d -. !cur_d in
      f := !f -. dt /. 100.0 *. !cur_n;
      f := !f -. dt *. !leak_rate;
      if !f < 0.0 then false
      else begin
        begin
          match e with
          | Fuel n -> cur_n := n
          | Leak -> leak_rate := !leak_rate +. 1.0
          | Gas_station -> f := original_f
          | Mechanic -> leak_rate := 0.0
          | Goal -> ()
        end;
        cur_d := d;
        go events'
      end
  in
  go events

let () =
  try
    while true do
      let events = read_events () in
      let ans = binsearch (can_events events) 0.0 10000.0 in
      printf "%.3f\n" ans;
    done
  with Exit -> ()
