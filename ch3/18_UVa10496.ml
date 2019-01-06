(* Collecting Beepers *)

open Printf
open Scanf

let max_n = 11

let n = ref 0
let dist = Array.make_matrix max_n max_n 0
let memo = Array.make_matrix max_n (1 lsl (max_n-1)) (-1)  (* Karel + max 10 beepers *)

let rec tsp c mask =  (* mask stores the visited coordinates *)
  if mask = 1 lsl !n - 1 then dist.(c).(0)  (* return trip to close the loop *)
  else if memo.(c).(mask) <> -1 then memo.(c).(mask)
  else begin
    let ans = ref 2_000_000_000 in
    for nxt = 1 to !n do  (* O(n) here *)
      if mask land 1 lsl (nxt-1) = 0 then  (* if coordinate nxt is not visited yet *)
        ans := min !ans (dist.(c).(nxt) + tsp nxt (mask lor 1 lsl (nxt-1)))
    done;
    memo.(c).(mask) <- !ans;
    memo.(c).(mask)
  end

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for _ = 1 to tc do
    scanf "%d %d\n" (fun _ _ -> ());  (* these two values are not used *)
    let x = Array.make 11 0 in
    let y = Array.make 11 0 in
    scanf "%d %d\n" (fun a b -> x.(0) <- a; y.(0) <- b);
    scanf "%d\n" (fun a -> n := a);
    for i = 1 to !n do  (* karel's position is at index 0 *)
      scanf "%d %d\n" (fun a b -> x.(i) <- a; y.(i) <- b)
    done;
    for i = 0 to !n do  (* build distance table *)
      for j = 0 to !n do
        dist.(i).(j) <- abs (x.(i)-x.(j)) + abs (y.(i)-y.(j))  (* Manhattan distance *)
      done
    done;
    Array.iter (fun a -> Array.fill a 0 (Array.length a) (-1)) memo;
    printf "The shortest path has length %d\n" (tsp 0 0)  (* DP-TSP *)
  done
