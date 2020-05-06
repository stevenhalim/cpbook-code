let failure_function pattern =
  let m = String.length pattern in
  let fail = Array.make (m + 1) (-1) in
  let i, j = ref 0, ref (-1) in
  while !i < m do
    while !j >= 0 && pattern.[!i] <> pattern.[!j] do
      j := fail.(!j)
    done;
    incr i; incr j;
    fail.(!i) <- !j
  done;
  fail

let kmp_search text pattern fail =
  let n = String.length text in
  let m = String.length pattern in
  let i, j = ref 0, ref 0 in
  let matches = ref [] in
  while !i < n do
    while !j >= 0 && text.[!i] <> pattern.[!j] do
      j := fail.(!j)
    done;
    incr i; incr j;
    if !j = m then begin
      matches := !i - !j :: !matches;
      j := fail.(!j)
    end
  done;
  !matches |> List.rev

let () =
  let text = "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN" in
  let pattern = "SEVENTY SEVEN" in
  let fail = failure_function pattern in
  kmp_search text pattern fail
    |> List.iter (Printf.printf "P is found at index %d in T\n")

(* Rabin Karp's will be added soon *)
