open Printf
open Scanf
open Seq

module ISMaxPQ = Set.Make (struct
    type t = int * string
    let compare x y = compare y x
  end)

let rec take n seq () =
  if n == 0 then
    Nil
  else
    match seq() with
    | Nil -> Nil
    | Cons (x, next) -> Cons (x, take (n - 1) next)

let () =
  let pq = ref ISMaxPQ.empty in

  pq := ISMaxPQ.add (100, "john") !pq;
  pq := ISMaxPQ.add (10, "billy") !pq;
  pq := ISMaxPQ.add (20, "andy") !pq;
  pq := ISMaxPQ.add (100, "steven") !pq;
  pq := ISMaxPQ.add (70, "felix") !pq;
  pq := ISMaxPQ.add (2000, "grace") !pq;
  pq := ISMaxPQ.add (70, "martin") !pq;

  !pq |> ISMaxPQ.to_seq |> take 3
  |> Seq.iter (fun (money, name) ->
      printf "%s has %d $\n" name money)
