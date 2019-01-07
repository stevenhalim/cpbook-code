let bfs n edges source =
  let adj = Array.make n [] in
  edges |> List.iter (fun (u, v) ->
    adj.(u) <- v :: adj.(u);
    adj.(v) <- u :: adj.(v)
  );
  let dist = Array.make n (-1) in
  let parent = Array.make n (-1) in
  dist.(source) <- 0;
  let queue = Queue.create () in
  Queue.add source queue;
  while not (Queue.is_empty queue) do
    let u = Queue.pop queue in
    adj.(u) |> List.iter (fun v ->
      if dist.(v) = -1 then begin
        parent.(v) <- u;
        dist.(v) <- dist.(u) + 1;
        Queue.add v queue
      end
    )
  done;
  dist, parent

let shortest_path parent source target =
  let rec aux acc u =
    if u = source then u :: acc
    else aux (u :: acc) parent.(u)
  in aux [] target


module IMap = Map.Make (struct type t = int let compare = compare end)

(** Suboptimal implementation using functional data structures *)
let pure_bfs n edges source =
  let adj =
    let init = IMap.of_seq (Array.init n (fun u -> u, []) |> Array.to_seq) in
    edges |> List.fold_left (fun acc (u, v) ->
      let add u v =
        IMap.update u (fun (Some ws) -> Some (v :: ws)) in
      acc |> add u v |> add v u
    ) init in
  let rec visit dist layer height =
    if layer = [] then dist, []
    else
      let next_layer = layer |> List.map (fun u ->
        IMap.find u adj |> List.filter (fun v -> not (IMap.mem v dist))
      ) |> List.concat |> List.sort_uniq compare in
      let dist = dist |> IMap.add_seq (next_layer
                                       |> List.map (fun v -> (v, height + 1))
                                       |> List.to_seq) in
      let dist, layers = visit dist next_layer (height + 1) in
      dist, layer :: layers
  in visit (IMap.singleton source 0) [source] 0

let () =
  let open Scanf in
  let open Printf in
  let n, m = scanf "%d %d " (fun x y -> (x, y)) in
  let edges = List.init m (fun _ -> scanf " %d %d " (fun x y -> (x, y))) in
  let source = 5 in
  let dist, parent = bfs n edges source in
  let is_bipartite = edges |> List.for_all (fun (u, v) -> dist.(u) mod 2 <> dist.(v) mod 2) in
  let _, layers = pure_bfs n edges source in
  layers |> List.iteri (fun i layer ->
    printf "Layer %d:" i;
    layer |> List.iter (printf " %d");
    printf "\n"
  );
  printf "Is bipartite: %b\n" is_bipartite;
  shortest_path parent source 7 |> List.iter (printf "%d ");
  printf "\n"
