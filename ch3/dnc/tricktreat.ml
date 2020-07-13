(* Trick or Treat
 * Ternary Search *)

open Scanf
open Printf

let solve n =
  let xs = Array.make n 0. in
  let ys = Array.make n 0. in
  let lo = ref max_float in
  let hi = ref min_float in
  for i = 0 to n - 1 do
    scanf "%f %f\n" (fun x y -> xs.(i) <- x; ys.(i) <- y);
    lo := min !lo xs.(i);
    hi := max !hi xs.(i);
  done;

  let f x' = (* square of earliest meeting time if all n kids meet at coordinate (x, y = 0.0) *)
    let ans = ref min_float in
    Array.iter2
      (fun x y ->
        ans := max !ans ((x -. x') *. (x -. x') +. y *. y) (* avoid computing sqrt which is slow *)
      )
      xs ys;
    !ans
  in

  for i = 0 to 49 do                              (* similar as BSTA *)
    let delta = (!hi -. !lo) /. 3. in             (* 1/3rd of the range *)
    let m1 = !lo +. delta in                      (* 1/3rd away from lo *)
    let m2 = !hi -. delta in                      (* 1/3rd away from hi *)
    if f m1 > f m2 then lo := m1 else hi := m2    (* f is unimodal *)
  done;
  printf "%.10f %.10f\n" !lo (sqrt (f !lo))

let () =
  let rec loop () =
    let n = scanf " %d\n" (fun x -> x) in
    if n <> 0 then (
      solve n;
      loop ()
    )
  in
  loop ()
