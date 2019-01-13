open Scanf
open Printf

module ISet = Set.Make (struct type t = int let compare = compare end)

let solve case n =
  let drinks = Array.init n (fun _ -> scanf "%s\n" (fun x -> x)) in
  let drink_id =
    drinks
    |> Array.to_seqi
    |> Seq.map (fun (i, x) -> (x, i))
    |> Hashtbl.of_seq in
  let drink_id drink = Hashtbl.find drink_id drink in
  let m = scanf "%d\n" (fun x -> x) in
  let adj = Array.make n [] in
  let in_deg = Array.make n 0 in
  for i = 1 to m do
    let u, v = scanf "%s %s\n" (fun x y -> (drink_id x, drink_id y)) in
    adj.(u) <- v :: adj.(u);
    in_deg.(v) <- in_deg.(v) + 1
  done;

  (* Kahn's algorithm *)
  
  let rec topo_sort order queue =
    match ISet.min_elt_opt queue with
    | None -> List.rev order
    | Some u ->
      let queue = adj.(u) |> List.fold_left (fun q v ->
        in_deg.(v) <- in_deg.(v) - 1;
        if in_deg.(v) = 0 then ISet.add v q else q
      ) queue in
      topo_sort (u :: order) (ISet.remove u queue) in
  
  let order = in_deg
    |> Array.to_seqi
    |> Seq.filter_map (fun (u, deg) -> if deg = 0 then Some u else None)
    |> ISet.of_seq
    |> topo_sort [] in
  
  printf "Case #%d: Dilbert should drink beverages in this order:" case;
  order |> List.iter (fun i -> printf " %s" drinks.(i));
  printf ".\n\n"

let () =
  let rec loop case =
    try
      let n = scanf "%d\n" (fun x -> x) in
      solve case n;
      scanf "\n" ();
      loop (case + 1)
    with _ -> () in
  loop 1
