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
  prim    n edges |> printf "MST cost = %d (Prim's)\n"
