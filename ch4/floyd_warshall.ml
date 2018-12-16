let floyd_warshall (n : int) (edges : (int*int*int) list) : int array array =
  let dist = Array.make_matrix n n (max_int / 2) in
  for u = 0 to n - 1 do
    dist.(u).(u) <- 0
  done;
  edges |> List.iter (fun (u, v, w) ->
    dist.(u).(v) <- w (* Directed edge *)
  );
  for k = 0 to n - 1 do
    for u = 0 to n - 1 do
      for v = 0 to n - 1 do
        dist.(u).(v) <- min dist.(u).(v) (dist.(u).(k) + dist.(k).(v))
      done
    done
  done;
  dist

let () =
  let (n, m) = Scanf.scanf "%d %d\n" (fun x y -> (x, y)) in
  let edges = List.init m (fun _ -> Scanf.scanf "%d %d %d\n" (fun u v w -> (u, v, w))) in
  let dist = floyd_warshall n edges in
  for u = 0 to n - 1 do
    for v = 0 to n - 1 do
      Printf.printf "APSP(%d, %d) = %d\n" u v dist.(u).(v)
    done
  done
