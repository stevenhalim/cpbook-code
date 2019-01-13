open Scanf
open Printf

let solve n m =
  let adj = Array.make n [] in
  for i = 1 to m do
    let u, v = scanf "%d %d\n" (fun x y -> (x, y)) in
    adj.(u) <- v :: adj.(u);
    adj.(v) <- u :: adj.(v)
  done;
  let color = Array.make n (-1) in
  let q = Queue.create () in
  Queue.add 0 q;
  let is_bipartite = ref true in
  while not (Queue.is_empty q) && !is_bipartite do
    let u = Queue.pop q in
    adj.(u) |> List.iter (fun v ->
      if color.(v) = -1 then begin
        color.(v) <- 1 - color.(u);
        Queue.add v q
      end else if color.(u) = color.(v) then
        is_bipartite := false
    )
  done;
  printf "%sBICOLORABLE.\n" (if !is_bipartite then "" else "NOT ")

let () =
  let rec loop () =
    try
      let n, m = scanf "%d\n%d\n" (fun x y -> (x, y)) in
      solve n m;
      loop ()
    with _ -> () in
  loop ()
