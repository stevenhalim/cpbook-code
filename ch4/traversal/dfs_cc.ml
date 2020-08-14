open Scanf
open Printf

type graph = int list array (* Adjacency List representation *)

let range n = List.init n (fun x -> x)

(** Returns a list of DFS orderings of all connected components *)
let dfs (adj : graph) : int list list =
  let n = Array.length adj in
  let visited = Array.make n false in
  let rec visit order u =
    visited.(u) <- true;
    adj.(u) |> List.fold_left (fun order v ->
      if visited.(v) then order
      else visit order v
    ) (u :: order)
  in
  range n |> List.fold_left (fun components u ->
    if visited.(u) then components
    else (visit [] u |> List.rev) :: components
  ) [] |> List.rev


let () =
  let ic = Scanning.open_in "dfs_cc_in.txt" in
  let sc = object method nf = bscanf ic end in
  let n = sc#nf " %d " (fun x -> x) in
  let adj = Array.init n (fun _ ->
    sc#nf " %d " (fun degree ->
      List.init degree (fun _ -> sc#nf " %d %d " (fun v w -> v))) (* Ignoring weight *)
  ) in
  
  printf "Standard DFS Demo (the input graph must be UNDIRECTED)\n";
  let ccs = dfs adj in
  ccs |> List.iteri (fun i component ->
    printf "CC %d:" (i + 1);
    component |> List.iter (printf " %d");
    printf "\n"
  );
  ccs |> List.length |> printf "There are %d connected components\n";
