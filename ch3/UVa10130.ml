(* SuperSale *)

(* 0-1 Knapsack DP (Top-Down) *)

open Printf
open Scanf

let max_n = 1010
let max_w = 40

let n = ref 0
let vs = Array.make max_n 0
let ws = Array.make max_n 0
let memo = Array.make_matrix max_n max_w (-1)

let rec value id w =
  if id = !n || w = 0 then 0
  else if memo.(id).(w) <> -1 then memo.(id).(w)
  else begin
    memo.(id).(w) <-
      if ws.(id) > w then value (id + 1) w
      else max (value (id + 1) w) (vs.(id) + value (id + 1) (w - ws.(id)));
    memo.(id).(w)
  end

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for _ = 1 to tc do
    Array.iter (fun a -> Array.fill a 0 (Array.length a) (-1)) memo;
    scanf "%d\n" (fun x -> n := x);
    for i = 0 to !n - 1 do
      scanf "%d %d\n" (fun x y -> vs.(i) <- x; ws.(i) <- y)
    done;
    let g = scanf "%d\n" (fun x -> x) in
    let ans = ref 0 in
    for _ = 1 to g do
      let mw = scanf "%d\n" (fun x -> x) in
      ans := !ans + value 0 mw
    done;
    printf "%d\n" !ans
  done



(* 0-1 Knapsack DP (Bottom-Up) *)

(* open Printf
 * open Scanf
 * 
 * let max_n = 1010
 * let max_w = 40
 * 
 * let () =
 *   let tc = scanf "%d\n" (fun x -> x) in
 *   for _ = 1 to tc do
 *     let n = scanf "%d\n" (fun x -> x) in
 *     let vs = Array.make (n + 1) 0 in
 *     let ws = Array.make (n + 1) 0 in
 *     for i = 1 to n do
 *       scanf "%d %d\n" (fun x y -> vs.(i) <- x; ws.(i) <- y)
 *     done;
 *     let c = Array.make_matrix max_n max_w 0 in
 *     for i = 1 to n do
 *       for w = 1 to max_w - 1 do
 *         c.(i).(w) <-
 *           if ws.(i) > w then c.(i - 1).(w)
 *           else max c.(i - 1).(w) (vs.(i) + c.(i - 1).(w - ws.(i)))
 *       done
 *     done;
 *     let g = scanf "%d\n" (fun x -> x) in
 *     let ans = ref 0 in
 *     for _ = 1 to g do
 *       let mw = scanf "%d\n" (fun x -> x) in
 *       ans := !ans + c.(n).(mw)
 *     done;
 *     printf "%d\n" !ans
 *   done *)
