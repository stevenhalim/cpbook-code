open Printf
open Scanf

let row = Array.make 8 0
let a = ref 0
let b = ref 0
let line_counter = ref 0

let can_place r c =
  List.init c (fun i -> i) |> List.for_all (fun prev ->
      row.(prev) <> r && abs (row.(prev) - r) <> abs (prev - c))

let rec backtrack c =
  if c = 8 then begin
    line_counter := !line_counter+1;
    printf "%2d      %d" !line_counter (row.(0)+1);
    for j = 1 to 7 do
      printf " %d" (row.(j)+1);
    done;
    printf "\n"
  end
  else
    for r = 0 to 7 do
      if (c = !b) = (r = !a) && can_place r c then begin
        row.(c) <- r; backtrack (c+1)
      end
    done

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for i = 1 to tc do
    scanf "\n%d %d\n" (fun x y -> a := x-1; b := y-1);
    line_counter := 0;
    printf "SOLN       COLUMN\n";
    printf " #      1 2 3 4 5 6 7 8\n\n";
    backtrack 0;
    if i < tc then printf "\n"
  done
