open Scanf
open Printf

type graph = int array array (* Adjacency List representation *)

let hierholzer (adj : graph) (start : int) : int list =
  let n = Array.length adj in
  let idx = Array.make n 0 in
  let rec iter path = function
    | [] -> path
    | u :: stack' as stack ->
      if idx.(u) < Array.length adj.(u) then begin
        let v = adj.(u).(idx.(u)) in
        idx.(u) <- idx.(u) + 1;
        iter path (v :: stack)
      end else
        iter (u :: path) stack' in
  iter [] [start]


let () =
  let adj = [|
    [1; 6];
    [2];
    [3; 4];
    [0];
    [5];
    [0; 2];
    [5];
  |] |> Array.map Array.of_list in
  let answer = hierholzer adj 0 in
  answer |> List.iter (fun u -> printf "%c " (char_of_int (int_of_char 'A' + u)));
  printf "\n"
