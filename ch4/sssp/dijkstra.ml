module PQ = Set.Make (struct type t = int * int let compare = compare end)

module IMap = Map.Make (struct type t = int let compare = compare end)

let dijkstra (n : int) (edges : (int * int * int) list) (source : int) : int array =
  let adj = Array.make n [] in
  edges |> List.iter (fun (u, v, w) ->
    adj.(u) <- (w, v) :: adj.(u) (* Directed edge *)
  );
  let rec loop dist pq =
    match PQ.min_elt_opt pq with
    | None ->
      Array.init n (fun i -> match IMap.find_opt i dist with None -> -1 | Some d -> d)
      (* -1 for unreachable vertices *)
    | Some ((d, u) as e) ->
      let pq = PQ.remove e pq in
      if d > IMap.find u dist then loop dist pq
      else
        let (dist, pq) = adj.(u) |> List.fold_left (fun (dist, pq) (w, v) ->
          let dv = d + w in
          match IMap.find_opt v dist with
          | None -> (IMap.add v dv dist, PQ.add (dv, v) pq)
          | Some dv' ->
            if dv < dv' then (IMap.add v dv dist, PQ.add (dv, v) pq)
            else (dist, pq)
        ) (dist, pq)
        in
        loop dist pq
  in
  loop (IMap.singleton source 0) (PQ.singleton (0, source))

let duplicate edges = edges @ List.map (fun (u, v, w) -> (v, u, w)) edges

let () =
  let (n, m, s) = Scanf.scanf "%d %d %d\n" (fun x y z -> (x, y, z)) in
  let edges = List.init m (fun _ -> Scanf.scanf "%d %d %d\n" (fun u v w -> (u, v, w))) in
  dijkstra n edges s |> Array.iteri (fun u d ->
    Printf.printf "SSSP(%d, %d) = %d\n" s u d
  )
