open Scanf
open Printf

let solve case =
  let n, m, s, t = scanf "%d %d %d %d\n" (fun x y z t -> (x, y, z, t)) in
  let adj = Array.make n [] in
  for i = 1 to m do
    let u, v, w = scanf "%d %d %d\n" (fun x y z -> (x, y, z)) in
    adj.(u) <- (v, w) :: adj.(u);
    adj.(v) <- (u, w) :: adj.(v)
  done;
  (* SPFA algorithm *)
  let dist = Array.make n max_int in
  let in_queue = Array.make n false in
  let q = Queue.create () in
  dist.(s) <- 0;
  Queue.add s q;
  in_queue.(s) <- true;
  while not (Queue.is_empty q) do
    let u = Queue.pop q in
    in_queue.(u) <- false;
    if dist.(u) = max_int then () else
    adj.(u) |> List.iter (fun (v, w) ->
      if dist.(u) + w < dist.(v) then begin
        dist.(v) <- dist.(u) + w;
        if not in_queue.(v) then begin
          Queue.add v q;
          in_queue.(v) <- true
        end
      end
    )
  done;
  printf "Case #%d: " case;
  if dist.(t) = max_int then printf "unreachable\n"
  else printf "%d\n" dist.(t)

let () =
  let tc = scanf "%d\n" (fun x -> x) in
  for i = 1 to tc do solve i done
