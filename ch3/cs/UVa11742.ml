open Printf
open Scanf

let rec permutations = function
  | [] -> Seq.return []
  | x::xs ->
    let rec interleave ys () =
      Seq.Cons (x::ys, match ys with
      | [] -> Seq.empty
      | y::ys' -> Seq.map (fun p -> y::p) (interleave ys')
      )
    in
    Seq.flat_map interleave (permutations xs)

let () =
  try
    while true do
      let n, m = scanf "%d %d\n" (fun x y -> x, y) in
      if n = 0 && m = 0 then raise Exit;
      let constraints = List.init m (fun _ ->
          scanf "%d %d %d\n" (fun a b c -> (a, b, c))) in
      let ok (a, b, c) p =
        let pos_a = List.nth p a in
        let pos_b = List.nth p b in
        let d_pos = abs (pos_a-pos_b) in
        if c > 0 then d_pos <= c else d_pos >= -c
      in
      let ans =
        Seq.fold_left
          (fun a p -> if List.for_all (fun c -> ok c p) constraints then a+1 else a)
          0
          (permutations (List.init n (fun i -> i)))
      in
      printf "%d\n" ans;
    done
  with Exit -> ()
