open Printf
open Scanf
open Seq

module ISMaxPQ = Set.Make (struct
    type t = int * string
    let compare x y = compare y x
  end)

let () =
  let pq = ref ISMaxPQ.empty in

  pq := ISMaxPQ.add (100, "john") !pq;
  pq := ISMaxPQ.add (10, "billy") !pq;
  pq := ISMaxPQ.add (20, "andy") !pq;
  pq := ISMaxPQ.add (100, "steven") !pq;
  pq := ISMaxPQ.add (70, "felix") !pq;
  pq := ISMaxPQ.add (2000, "grace") !pq;
  pq := ISMaxPQ.add (70, "martin") !pq;

  for _ = 1 to 3 do
    let (money, name) as result = ISMaxPQ.min_elt !pq in
    pq := ISMaxPQ.remove result !pq;
    printf "%s has %d $\n" name money
  done;
