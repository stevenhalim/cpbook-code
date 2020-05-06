module S = String

let compute_table a b =
  let n = S.length a in
  let m = S.length b in
  let table = Array.make_matrix (n+1) (m+1) 0 in
  (* insert/delete = -1 point *)
  for i = 1 to n do
    table.(i).(0) <- i * (-1)
  done;
  for j = 1 to m do
    table.(0).(j) <- j * (-1)
  done;
  for i = 1 to n do
    for j = 1 to m do
      (* match = 2 points, mismatch = -1 point *)
      table.(i).(j) <-
        max (table.(i-1).(j-1) + if a.[i-1] = b.[j-1] then 2 else -1)
            (-1 + max table.(i-1).(j) table.(i).(j-1)) (* insert/delete *)
    done
  done;
  table

let () =
  let a = "ACAATCC" in
  let b = "AGCATGC" in
  let table = compute_table a b in
  let open Printf in
  printf "DP table:\n";
  table |> Array.iter (fun row ->
    row |> Array.iter (printf "%3d");
    printf "\n"
  );
  printf "Maximum Alignment Score: %d\n" table.(S.length a).(S.length b)