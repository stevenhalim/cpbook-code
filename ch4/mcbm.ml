(** [mcbm v_left v_right edges] returns a maximum cardinality bipartite matching.
    Left side are numbered [0..v_left-1], right side [0..v_right-1].
    Set both [v_left] and [v_right] to [V] for mixed indices [0..V-1]*)
let mcbm v_left v_right edges =
  let adj_l = Array.make v_left [] in
  edges |> List.iter (fun (l, r) -> adj_l.(l) <- r :: adj_l.(l));
  let match_r = Array.make v_right (-1) in
  let visited_l = Array.make v_left false in
  let rec aug l =
    if visited_l.(l) then false
    else begin
      visited_l.(l) <- true;
        match adj_l.(l)
          |> List.find_opt (fun r -> match_r.(r) = -1 || aug match_r.(r)) with
        | Some r -> 
            match_r.(r) <- l;
            true
        | None -> false
    end
  in
  (** Greedy pre-processing for trivial Augmenting Paths *)
  let free_l = List.init v_left (fun x -> x) |> List.filter (fun l ->
    let candidates = adj_l.(l) |> List.filter (fun r -> match_r.(r) = -1) in
    if List.length candidates > 0 then
      let i = Random.int (List.length candidates) in
      match_r.(List.nth candidates i) <- l;
      false
    else true
  )
  in
  free_l |> List.iter (fun l->
    let _ = aug l in
    Array.fill visited_l 0 v_left false
  );
  match_r |> Array.to_list
    |> List.mapi (fun r l -> (l, r)) |> List.filter (fun (l, r) -> l <> -1)


let () =
  mcbm 5 5 [(1, 3); (1, 4); (2, 3)]
    |> List.length
    |> Printf.printf "Found %d matchings\n"
