open Scanf
open Printf

let range n = Array.init n (fun x -> x)

type graph = int list array (* Adjacency List representation *)

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
  range n |> Array.iter (fun u -> if num.(u) = -1 then visit u);
  !sccs

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
