open Printf

module ISet = Set.Make (struct type t = int let compare = compare end)
module SMap = Map.Make (struct type t = string let compare = compare end)

let () =
  let mapper = [
      ("john", 78);
      ("billy", 69);
      ("andy", 80);
      ("steven", 77);
      ("felix", 82);
      ("grace", 75);
      ("martin", 81);
    ] |> List.to_seq |> SMap.of_seq in
  let used_values = SMap.to_seq mapper |> Seq.map snd |> ISet.of_seq in

  SMap.iter (fun k v -> printf "%s %d\n" k v) mapper;

  printf "steven's score is %d, grace's score is %d\n"
    (SMap.find "steven" mapper) (SMap.find "grace" mapper);
  printf "==================\n";

  let iter_while pred f seq =
    let rec go seq =
      match seq () with
      | Seq.Nil -> ()
      | Seq.Cons (x, seq') -> if pred x then (f x; go seq') else ()
    in
    go seq in

  SMap.to_seq_from "f" mapper
  |> iter_while (fun (k, v) -> k < "m")
    (fun (k, v) -> printf "%s %d\n" k v);

  printf "%d\n" (ISet.find 77 used_values);

  ISet.to_seq used_values |> iter_while (fun x -> x < 77) (printf "%d,");
  printf "\n";

  ISet.to_seq_from 77 used_values |> Seq.iter (printf "%d,");
  printf "\n";

  match ISet.find_opt 79 used_values with
  | None -> printf "79 not found\n"
  | _ -> ();
