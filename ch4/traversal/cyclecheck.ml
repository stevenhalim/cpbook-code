open Scanf
open Printf

type graph = int list array (* Adjacency List representation *)

type vertex_state = White | Gray | Black

let graph_check (adj : graph) =
  let n = Array.length adj in
  let color = Array.make n White in
  let parent = Array.make n (-1) in
  let bidirectionals = ref [] in
  let backs = ref [] in
  let forward_cross = ref [] in
  let rec visit u =
    color.(u) <- Gray;
    adj.(u) |> List.iter (fun v ->
      match color.(v) with
      | White -> parent.(v) <- u; visit v
      | Gray ->
        if v = parent.(u) then bidirectionals := (u, v) :: !bidirectionals
        else backs := (u, v) :: !backs
      | Black -> forward_cross := (u, v) :: !forward_cross
    );
    color.(u) <- Black
  in
  List.init n (fun x -> x) |> List.iter (fun u -> if color.(u) = White then visit u);
  !bidirectionals, !backs, !forward_cross

let () =
  let ic = Scanning.open_in "scc_in.txt" in
  let sc = object method nf = bscanf ic end in
  let n = sc#nf " %d " (fun x -> x) in
  let adj = Array.init n (fun _ ->
    sc#nf " %d " (fun degree ->
      List.init degree (fun _ -> sc#nf " %d %d " (fun v w -> v))) (* Ignoring weight *)
  ) in
  printf "Graph Edges Property Check\n";
  let bidirectionals, backs, forward_cross = graph_check adj in
  bidirectionals |> List.iter (fun (u, v) ->
    printf " Bidirectional (%d, %d) - (%d, %d)\n" u v v u);
  backs |> List.iter (fun (u, v) ->
    printf " Back Edge (%d, %d) (Cycle)\n" u v
  );
  forward_cross |> List.iter (fun (u, v) ->
    printf " Forward/Cross Edge (%d, %d)\n" u v
  );
