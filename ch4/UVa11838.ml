open Scanf
open Printf

let range n = Array.init n (fun x -> x)

let kosaraju adj_list adj_list_t =
  let n = Array.length adj_list in
  let visited = Array.make n false in

  let rec dfs adj order u =
    visited.(u) <- true;
    u :: (adj.(u) |> List.fold_left (fun acc v ->
        if visited.(v) then acc else dfs adj acc v
      ) order) in
  
  let order =
    range n |> Array.fold_left (fun acc u ->
      if visited.(u) then acc else dfs adj_list acc u ) [] in
  
  Array.fill visited 0 n false;
  order |> List.fold_left (fun sccs u ->
    if visited.(u) then sccs else dfs adj_list_t [] u :: sccs ) []

let solve n m =
  let adj = Array.make n [] in
  let adj' = Array.make n [] in
  for _ = 1 to m do
    let u, v, t = scanf "%d %d %d\n" (fun x y z -> (x - 1, y - 1, z)) in
    adj.(u) <- v :: adj.(u);
    adj'.(v) <- u :: adj'.(v);
    if t = 2 then begin (* if this is two way, add the reverse direction *)
      adj.(v) <- u :: adj.(v);
      adj'.(u) <- v :: adj'.(u);
    end
  done;
  let sccs = kosaraju adj adj' in
  if List.length sccs = 1 then printf "1\n"
  else printf "0\n"

let () =
  let rec loop () =
    let n, m = scanf "%d %d\n" (fun x y -> (x, y)) in
    if n = 0 && m = 0 then ()
    else begin
      solve n m;
      loop ()
    end in
  loop ()
