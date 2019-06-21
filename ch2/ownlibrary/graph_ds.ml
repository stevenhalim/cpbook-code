open Printf
open Scanf

module IIIMinPQ = Set.Make (struct
    type t = int * int * int
    let compare = compare
  end)

let () =
 (* Try this input for Adjacency Matrix/Adjacency List/Edge List
  * Adjacency Matrix am
  *   for each line: |v| entries, 0 or the weight
  * Adjacency List al
  *   for each line: num neighbors, list of neighbors + weight pairs
  * Edge List el
  *   for each line: a-b of edge(a,b) and weight *)

  (* 6
   *   0  10   0   0 100   0
   *  10   0   7   0   8   0
   *   0   7   0   9   0   0
   *   0   0   9   0  20   5
   * 100   8   0  20   0   0
   *   0   0   0   5   0   0
   * 6
   * 2 2 10 5 100
   * 3 1 10 3 7 5 8
   * 2 2 7 4 9
   * 3 3 9 5 20 6 5
   * 3 1 100 2 8 4 20
   * 1 4 5
   * 7
   * 1 2 10
   * 1 5 100
   * 2 3 7
   * 2 5 8
   * 3 4 9
   * 4 5 20
   * 4 6 5 *)

  let ic = Scanning.open_in "graph_ds.txt" in

  let v = bscanf ic "%d\n" (fun x -> x) in  (* we must know this size first! *)
                         (* remember that if v is > 2000, try NOT to use am! *)
  let am = Array.init v (fun _ ->
      Array.init v (fun _ ->
          bscanf ic " %d" (fun x -> x)
        )
    ) in

  printf "Neighbors of vertex 0:\n";
  am.(0) |> Array.iteri (fun j x ->  (* O(|v|) *)
      if x <> 0 then
        printf "Edge 0-%d (weight = %d)\n" j x
    );

  let v = bscanf ic " %d\n" (fun x -> x) in
  let al = Array.init v (fun _ ->
    let total_neighbors = bscanf ic "%d " (fun x -> x) in
    List.init total_neighbors (fun _ ->
        bscanf ic "%d %d " (fun id weight -> (id - 1, weight))  (* some index adjustment *)
      )
    ) in
  printf "Neighbors of vertex 0:\n";
  al.(0) |> List.iter (fun (v, w) ->
      (* al.(0) contains the required information *)
      (* O(k), where k is the number of neighbors *)
      printf "Edge 0-%d (weight = %d)\n" v w
    );

  let e = bscanf ic "%d\n" (fun x -> x) in
  let el = List.init e (fun _ ->
      bscanf ic "%d %d %d\n" (fun a b weight -> (weight, a, b))
    ) |> IIIMinPQ.of_list  (* one way to store Edge list *)
  in

  (* edges sorted by weight (smallest->largest) *)
  el |> IIIMinPQ.iter (fun (weight, a, b) ->
      printf "weight: %d (%d-%d)\n" weight a b
    );
