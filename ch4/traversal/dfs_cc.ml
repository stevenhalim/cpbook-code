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

(* Returns an array of colors of the vertices *)
let floodfill (adj : graph) : int array =
  let n = Array.length adj in
  let label = Array.make n (-1) in
  let rec visit u color =
    label.(u) <- color;
    adj.(u) |> List.iter (fun v ->
      if label.(v) = -1 then visit v color
    )
  in
  let ncc = ref 0 in
  for u = 0 to n - 1 do
    if label.(u) = -1 then begin
      incr ncc;
      visit u !ncc
    end
  done;
  label

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
  range n |> List.fold_left (fun acc u ->
    if visited.(u) then acc
    else visit acc u 
  ) []

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
  range n |> List.iter (fun u -> if color.(u) = White then visit u);
  !bidirectionals, !backs, !forward_cross

(** Returns a list of all articulation points and a list of all bridges of the
    simple graph.
    For multigraphs, store edge ids to the adjacency lists to check for
    bidirectional edges instead of using [parent] *)
let articulation_point_and_bridge (adj : graph) : int list * (int*int) list =
  let n = Array.length adj in
  let low = Array.make n 0 in
  let num = Array.make n (-1) in
  let parent = Array.make n (-1) in
  let counter = ref 0 in
  let rec visit u =
    low.(u) <- !counter;
    num.(u) <- !counter;
    incr counter;
    adj.(u) |> List.iter (fun v ->
      if num.(v) = -1 then begin
        parent.(v) <- u;
        visit v;
        low.(u) <- min low.(u) low.(v)
      end
      else if v <> parent.(u) then (** Use edge id for multigraphs *)
        low.(u) <- min low.(u) num.(v)
    )
  in
  range n |> List.iter (fun u ->
    if num.(u) = -1 then begin
      counter := 0;
      visit u
    end
  );
  let articulation_points = range n |> List.filter (fun u ->
    if num.(u) = 0 then (* special case for root *)
      adj.(u) |> List.filter (fun v -> parent.(v) = u) |> List.length > 1
    else adj.(u) |> List.exists (fun v -> parent.(v) = u && low.(v) >= num.(u))
  ) in
  let bridges = range n |> List.map (fun u ->
    adj.(u)
      |> List.filter (fun v -> parent.(v) = u && low.(v) > num.(u))
      |> List.map (fun v -> (u, v))
  ) |> List.concat in
  articulation_points, bridges

(** Returns a list of all strongly connected components of the directed graph *)
let tarjan_scc (adj : graph) : int list list =
  let n = Array.length adj in
  let low = Array.make n 0 in
  let num = Array.make n (-1) in
  let counter = ref 0 in
  let stack = ref [] in
  let on_stack = Array.make n false in
  let sccs = ref [] in
  let rec visit u =
    low.(u) <- !counter;
    num.(u) <- !counter;
    incr counter;
    stack := u :: !stack;
    on_stack.(u) <- true;
    adj.(u) |> List.iter (fun v ->
      if num.(v) = -1 then begin
        visit v;
        low.(u) <- min low.(u) low.(v)
      end
      else if on_stack.(v) then
        low.(u) <- min low.(u) num.(v)
    );
    if low.(u) = num.(u) then begin
      let rec pop_scc acc = function
        | hd :: tl ->
          if hd = u then hd :: acc, tl
          else pop_scc (hd :: acc) tl
        | [] -> assert false
      in
      let scc, stack' = pop_scc [] !stack in
      stack := stack';
      scc |> List.iter (fun v -> on_stack.(v) <- false);
      sccs := scc :: !sccs
    end
  in
  range n |> List.iter (fun u -> if num.(u) = -1 then visit u);
  !sccs

let print message =
  printf "==================================\n";
  printf "%s\n" message;
  printf "==================================\n"


let () =
  let ic = Scanning.open_in "01_in.txt" in
  let sc = object method nf = bscanf ic end in
  let n = sc#nf " %d " (fun x -> x) in
  let adj = Array.init n (fun _ ->
    sc#nf " %d " (fun degree ->
      List.init degree (fun _ -> sc#nf " %d %d " (fun v w -> v))) (* Ignoring weight *)
  ) in
  
  print "Standard DFS Demo (the input graph must be UNDIRECTED)";
  let ccs = dfs adj in
  ccs |> List.iteri (fun i component ->
    printf "CC %d:" (i + 1);
    component |> List.iter (printf " %d");
    printf "\n"
  );
  ccs |> List.length |> printf "There are %d connected components\n";

  print "Flood Fill Demo (the input graph must be UNDIRECTED)";
  floodfill adj |> Array.iteri (printf "Vertex %d has color %d\n");
  
  print "Topological Sort (the input graph must be DAG)";
  topo_sort adj |> List.iter (printf " %d"); printf "\n";

  print "Graph Edges Property Check";
  let bidirectionals, backs, forward_cross = graph_check adj in
  bidirectionals |> List.iter (fun (u, v) ->
    printf " Bidirectional (%d, %d) - (%d, %d)\n" u v v u);
  backs |> List.iter (fun (u, v) ->
    printf " Back Edge (%d, %d) (Cycle)\n" u v
  );
  forward_cross |> List.iter (fun (u, v) ->
    printf " Forward/Cross Edge (%d, %d)\n" u v
  );

  print "Articulation Points & Bridges (the input graph must be UNDIRECTED)";
  let aps, bridges = articulation_point_and_bridge adj in
  printf "Bridges:\n";
  bridges |> List.iter (fun (u, v) -> printf " Edge (%d, %d) is a bridge\n" u v);
  printf "Articulation Points:\n";
  aps |> List.iter (printf " Vertex %d\n");

  print "Strongly Connected Components (the input graph must be DIRECTED)";
  tarjan_scc adj |> List.iteri (fun i scc ->
    printf "SCC %d:" (i + 1);
    scc |> List.iter (printf " %d");
    printf "\n"
  )
