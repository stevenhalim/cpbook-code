let bellman_ford (n : int) (edges : (int*int*int) list) (source : int) : int array option =
  let adj = Array.make n [] in
  edges |> List.iter (fun (u, v, w) ->
    adj.(u) <- (w, v) :: adj.(u) (* Directed edge *)
  );
  let dist = Array.make n max_int in
  dist.(source) <- 0;
  for _ = 1 to n - 1 do
    for u = 0 to n - 1 do
      if dist.(u) <> max_int then
        adj.(u) |> List.iter (fun (w, v) ->
          dist.(v) <- min dist.(v) (dist.(u) + w)
        )
    done
  done;
  let has_neg_cycle = List.init n (fun x -> x) |> List.exists (fun u ->
    dist.(u) <> max_int && adj.(u) |> List.exists (fun (w, v) ->
      dist.(v) > dist.(u) + w
    )
  ) in
  if has_neg_cycle then None
  else Some dist

let () =
  let (n, m, s) = Scanf.scanf "%d %d %d\n" (fun x y z -> (x, y, z)) in
  let edges = List.init m (fun _ -> Scanf.scanf "%d %d %d\n" (fun u v w -> (u, v, w))) in
  match bellman_ford n edges s with
  | Some dist -> dist |> Array.iteri (fun u d ->
      Printf.printf "SSSP(%d, %d) = %d\n" s u d
    )
  | None -> Printf.printf "The graph has a negative cycle"
