open Printf

let max_n = 1000

let children = Array.make max_n []

let l = Array.make (2*max_n) 0
let e = Array.make (2*max_n) 0
let h = Array.make max_n (-1)
let idx = ref 0

let rec dfs cur depth =
  h.(cur) <- !idx;
  e.(!idx) <- cur;
  l.(!idx) <- depth;
  idx := !idx+1;
  children.(cur) |> List.iter (fun nxt ->
      dfs nxt (depth+1);
      e.(!idx) <- cur;                      (* backtrack to current node *)
      l.(!idx) <- depth;
      idx := !idx+1
    )

let build_rmq () =
  dfs 0 0                       (* we assume that the root is at index 0 *)

let () =
  children.(0) <- [1; 7];
  children.(1) <- [2; 3; 6];
  children.(3) <- [4; 5];
  children.(7) <- [8; 9];

  build_rmq ();
  for i = 0 to 2*10-2 do
    printf "%d " h.(i)
  done;
  printf "\n";
  for i = 0 to 2*10-2 do
    printf "%d " e.(i)
  done;
  printf "\n";
  for i = 0 to 2*10-2 do
    printf "%d " l.(i)
  done;
  printf "\n";
