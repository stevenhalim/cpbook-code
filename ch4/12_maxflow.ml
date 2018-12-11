open Scanf
open Printf

module Dinic = struct
  type edge = { v: int; cap: int; flow: int ref }

  type t = {
    n: int;
    redges: edge array;
    adj: int list array;
    dist: int array
  }

  let create_graph n edges =
    let m = Array.length edges in
    let redges = Array.make (m*2) { v=0; cap=0; flow=ref 0 } in
    let adj = Array.make n [] in
    for i = 0 to m-1 do
      let (u, v, cap) = edges.(i) in
      redges.(2*i) <- { v=v; cap; flow=ref 0 };
      redges.(2*i+1) <- { v=u; cap=0; flow=ref 0; };
      adj.(u) <- (2*i) :: adj.(u);
      adj.(v) <- (2*i+1) :: adj.(v)
    done;
    { n; redges; adj; dist = Array.make n n }

  let rcap { cap; flow } = cap - !flow

  let bfs { n; redges; adj; dist } source sink =
    let queue = Queue.create () in
    Queue.add source queue;
    Array.fill dist 0 n n;
    dist.(source) <- 0;
    while not (Queue.is_empty queue) do
      let u = Queue.pop queue in
      adj.(u) |> List.iter (fun i ->
        let e = redges.(i) in
        if rcap e > 0 && dist.(e.v) > dist.(u) + 1 then begin
          dist.(e.v) <- dist.(u) + 1;
          Queue.add e.v queue
        end
      )
    done;
    dist.(sink) < n
  
  let dfs { redges; adj; dist } start source sink =
    let rec go u flow =
      if u = sink then flow
      else
        let rec loop () = match start.(u) with
          | [] -> 0
          | hd::tl ->
            let e = redges.(hd) in
            let e' = redges.(hd lxor 1) in
            let aug = ref 0 in
            if rcap e > 0 && dist.(e.v) = dist.(u) + 1 &&
              (aug := go e.v (min flow (rcap e)); !aug > 0) then
                begin
                  e.flow := !(e.flow) + !aug;
                  e'.flow := !(e'.flow) - !aug;
                  !aug
                end
            else (start.(u) <- tl; loop ())
        in loop ()
    in go source max_int

  let max_flow graph source sink =
    let total = ref (Int64.of_int 0) in
    let start = Array.copy graph.adj in
    while bfs graph source sink do
      let flow = ref 0 in
      while flow := dfs graph start source sink; !flow > 0 do
        total := Int64.add !total (Int64.of_int !flow)
      done;
      Array.blit graph.adj 0 start 0 graph.n;
    done;
    !total
end

let read_edges n =
  List.init n (fun u ->
    let deg = scanf "%d" (fun x -> x) in
    let edges = Array.init deg (fun _ -> scanf " %d %d" (fun v c -> (u, v, c))) in
    let () = scanf "\n" () in edges
  ) |> Array.concat

let () =
  let (n, s, t) = scanf "%d %d %d\n" (fun a b c -> (a, b, c)) in
  let graph = Dinic.create_graph n
                (read_edges n) in
  printf "%Ld\n" (Dinic.max_flow graph s t)
