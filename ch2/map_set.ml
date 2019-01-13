open Printf
open Seq

module ISet = Set.Make (struct type t = int let compare = compare end)
module SMap = Map.Make (struct type t = string let compare = compare end)

let rec take_while pred seq () =
  match seq () with
  | Nil -> Nil
  | Cons (x, next) -> if pred x then Cons (x, take_while pred next) else Nil

let () =
  (* suppose we enter these 7 name-score pairs below *)
  (* john 78
   * billy 69
   * andy 80
   * steven 77
   * felix 82
   * grace 75
   * martin 81 *)

  let mapper = [
      ("john", 78);
      ("billy", 69);
      ("andy", 80);
      ("steven", 77);
      ("felix", 82);
      ("grace", 75);
      ("martin", 81);
    ] |> List.to_seq |> SMap.of_seq in
  let used_values = SMap.to_seq mapper |> map snd |> ISet.of_seq in

  (* then the internal content of mapper MAY be something like this:
   * re-read balanced BST concept if you do not understand this diagram
   * the keys are names (string)!
   *                        (grace,75)
   *           (billy,69)               (martin,81)
   *     (andy,80)   (felix,82)    (john,78)  (steven,77) *)

  (* iterating through the content of mapper will give a sorted output
   * based on keys (names) *)
  SMap.iter (fun k v -> printf "%s %d\n" k v) mapper;

  (* Map can also be used like this *)
  printf "steven's score is %d, grace's score is %d\n"
    (SMap.find "steven" mapper) (SMap.find "grace" mapper);
  printf "==================\n";

  (* interesting usage of to_seq_from
   * display data between ["f".."m") ('felix' is included, 'martin' is excluded) *)
  SMap.to_seq_from "f" mapper |> take_while (fun (k, _) -> k < "m")
  |> iter (fun (k, v) -> printf "%s %d\n" k v);

  (* the internal content of used_values MAY be something like this
   * the keys are values (integers)!
   *                 (78)
   *         (75)            (81)
   *     (69)    (77)    (80)    (82) *)

  (* O(log n) search, found *)
  printf "%d\n" (ISet.find 77 used_values);
  (* returns [69, 75] (these two are before 77 in the inorder traversal of this BST) *)
  ISet.to_seq used_values |> take_while (fun x -> x < 77)
  |> iter (printf "%d,");
  printf "\n";
  (* returns [77, 78, 80, 81, 82] (these five are equal or after 77 in the inorder traversal of this BST) *)
  ISet.to_seq_from 77 used_values |> iter (printf "%d,");
  printf "\n";
  (* O(log n) search, not found *)
  match ISet.find_opt 79 used_values with
  | None -> printf "79 not found\n"
  | _ -> ()
