module UnionFind = struct
  type t =
    { parent: int array;
      rank: int array;
      size: int array;
      num_sets: int ref;
    }
  
  let create n =
    { parent  = Array.init n (fun x -> x);
      rank    = Array.make n 0;
      size    = Array.make n 1;
      num_sets = ref n;
    }
  
  let find { parent } u =
    let rec aux u =
      if parent.(u) = u then u
      else begin
        parent.(u) <- aux parent.(u);
        parent.(u)
      end
    in aux u
  
  let is_same_set dsu u v = find dsu u = find dsu v

  let union dsu u v =
    let link x p =
      dsu.parent.(x) <- p;
      dsu.size.(p) <- dsu.size.(p) + dsu.size.(x);
      if dsu.rank.(x) = dsu.rank.(p) then
        dsu.rank.(p) <- dsu.rank.(p) + 1
    in
    let pu, pv = find dsu u, find dsu v in
    if pu = pv then ()
    else begin
      decr dsu.num_sets;
      if dsu.rank.(pu) > dsu.rank.(pv) then link pv pu
      else link pu pv
    end
  
  let num_disjoint_sets { num_sets } = !num_sets

  let size_of_set dsu u = dsu.size.(find dsu u)
end

(** [kruskal n edges] returns the total weight of a MST of the input graph [(0..n-1, edges)] *)
let kruskal n edges =
  let dsu = UnionFind.create n in
  let cost = ref 0 in
  edges
    |> List.sort (fun (_, _, w1) (_, _, w2) -> compare w1 w2)
    |> List.iter (fun (u, v, w) ->
        if not (UnionFind.is_same_set dsu u v) then begin
          UnionFind.union dsu u v;
          cost := !cost + w
        end
      );
  !cost


module PQ = Set.Make (struct
  type t = int * int
  let compare = compare
end)

module IntS = Set.Make (struct
  type t = int
  let compare = compare
end)

(** [prim n edges] returns the total weight of a MST of the input graph [(0..n-1, edges)] *)
let prim n edges =
  let adj = Array.make n [] in
  edges |> List.iter (fun (u, v, w) ->
    adj.(u) <- (w, v) :: adj.(u);
    adj.(v) <- (w, u) :: adj.(v)
  );
  let rec loop taken candidates cost =
    match PQ.min_elt_opt candidates with
    | None -> cost
    | Some ((w, u) as e) ->
      let candidates = PQ.remove e candidates in
      if IntS.mem u taken then loop taken candidates cost
      else loop (IntS.add u taken)
                (candidates |> PQ.add_seq (List.to_seq adj.(u)))
                (cost + w)
  in loop (IntS.singleton 0) (PQ.of_list adj.(0)) 0

open Scanf
open Printf

let sc = object method nf = bscanf Scanning.stdin end

let () =
  let (n, m) = sc#nf "%d %d\n" (fun x y -> (x, y)) in
  let edges = List.init m (fun _ -> sc#nf "%d %d %d\n" (fun u v w -> (u, v, w))) in
  kruskal n edges |> printf "MST cost = %d (Kruskal's)\n";
  prim    n edges |> printf "MST cost = %d (Prim's)\n"
