open Scanf
open Printf

type graph = int list array (* Adjacency List representation *)

(** Return a topological ordering of the DAG *)
let topo_sort (adj : graph) : int list =
  let n = Array.length adj in
  let visited = Array.make n false in
  let rec visit order u =
    visited.(u) <- true;
    u ::
      (adj.(u) |> List.fold_left (fun order v ->
        if visited.(v) then order
        else visit order v
      ) order)
  in
  List.init n (fun x -> x) |> List.fold_left (fun acc u ->
    if visited.(u) then acc
    else visit acc u 
  ) []

let () =
  let ic = Scanning.open_in "toposort_in.txt" in
  let sc = object method nf = bscanf ic end in
  let n = sc#nf " %d " (fun x -> x) in
  let adj = Array.init n (fun _ ->
    sc#nf " %d " (fun degree ->
      List.init degree (fun _ -> sc#nf " %d %d " (fun v w -> v))) (* Ignoring weight *)
  ) in
  printf "Topological Sort (the input graph must be DAG)\n";
  topo_sort adj |> List.iter (printf " %d"); printf "\n";
