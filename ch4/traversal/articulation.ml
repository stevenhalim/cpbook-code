open Scanf
open Printf

type graph = int list array (* Adjacency List representation *)

let range n = List.init n (fun x -> x)

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

let () =
  let ic = Scanning.open_in "articulation_in.txt" in
  let sc = object method nf = bscanf ic end in
  let n = sc#nf " %d " (fun x -> x) in
  let adj = Array.init n (fun _ ->
    sc#nf " %d " (fun degree ->
      List.init degree (fun _ -> sc#nf " %d %d " (fun v w -> v))) (* Ignoring weight *)
  ) in
  printf "Articulation Points & Bridges (the input graph must be UNDIRECTED)\n";
  let aps, bridges = articulation_point_and_bridge adj in
  printf "Bridges:\n";
  bridges |> List.iter (fun (u, v) -> printf " Edge (%d, %d) is a bridge\n" u v);
  printf "Articulation Points:\n";
  aps |> List.iter (printf " Vertex %d\n");
