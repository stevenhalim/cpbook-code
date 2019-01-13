open Printf
open Scanf

module ISMaxPQ = Set.Make (struct
    type t = int * string
    let compare x y = compare y x
  end)

let () =
  (* suppose we enter these 7 money-name pairs below *)
  (* 100 john
   * 10 billy
   * 20 andy
   * 100 steven
   * 70 felix
   * 2000 grace
   * 70 martin *)
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
