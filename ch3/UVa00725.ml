open Printf
open Scanf

let digits n =
  let rec aux used n =
    match n with
    | 0 -> used
    | n -> aux (used lor 1 lsl (n mod 10)) (n / 10)
  in aux (if n < 10000 then 1 else 0) n

let () =
  let first = ref true in
  try
    while true do
      let n = scanf "%d\n" (fun x -> x) in
      if n = 0 then raise Exit;
      if not !first then printf "\n";
      first := false;
      let no_solution = ref true in
      for fghij = 1234 to 98765/n do
        let abcde = fghij * n in
        let used = digits abcde lor digits fghij in
        if used = 1 lsl 10 - 1 then begin
          printf "%0.5d / %0.5d = %d\n" abcde fghij n;
          no_solution := false;
        end
      done;
      if !no_solution then printf "There are no solutions for %d.\n" n;
    done
  with Exit ->
    ()
