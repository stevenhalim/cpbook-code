open Printf
open Scanf

module IIIMinPQ = Set.Make (struct
    type t = int * int * int
    let compare = compare
  end)

let () =
  let ic = Scanning.open_in "07_in.txt" in

  let v = bscanf ic " %d\n" (fun x -> x) in
  let am = Array.init v (fun _ ->
      Array.init v (fun _ ->
          bscanf ic " %d" (fun x -> x)
        )
    ) in

  printf "Neighbors of vertex 0:\n";
  am.(0) |> Array.iteri (fun j x ->
      if x <> 0 then
        printf "Edge 0-%d (weight = %d)\n" j x
    );

  let v = bscanf ic " %d\n" (fun x -> x) in
  let al = Array.init v (fun _ ->
    let total_neighbors = bscanf ic " %d" (fun x -> x) in
    List.init total_neighbors (fun _ ->
        bscanf ic " %d %d" (fun x y -> (x - 1, y))
      )
    ) in
  printf "Neighbors of vertex 0:\n";
  al.(0) |> List.iter (fun (v, w) ->
      printf "Edge 0-%d (weight = %d)\n" v w
    );

  let e = bscanf ic " %d\n" (fun x -> x) in
  let el = List.init e (fun _ ->
      bscanf ic " %d %d %d" (fun a b weight -> (weight, a, b))
    ) |> IIIMinPQ.of_list in

  el |> IIIMinPQ.iter (fun (weight, a, b) ->
      printf "weight: %d (%d-%d)\n" weight a b
    );
