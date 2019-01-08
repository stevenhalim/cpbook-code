open Scanf
open Printf

let () =
  (* comment all lines and only uncomment demo code that you are interested with *)

  let ic = Scanning.open_in "IO_in1.txt" in 
  bscanf ic "%d\n" (fun tc ->
    for i = 1 to tc do 
      bscanf ic "%d %d\n" (fun a b ->
        printf "%d\n" (a+b)
      )
    done
  )

(*   let ic = Scanning.open_in "IO_in2.txt" in
  let rec process () =
    bscanf ic "%d %d\n" (fun a b ->
      if a = 0 && b = 0 then ()
      else begin
        printf "%d\n" (a+b);
        process ()
      end
    )
  in 
  process () *)

(*   let ic = Scanning.open_in "IO_in3.txt" in 
  try
    let case = ref 1 in
    while true do 
      bscanf ic "%d %d\n" (fun a b ->
        printf "Case %d: %d\n\n" !case (a+b);
        incr case
      )
    done
  with End_of_file ->
    () *)

(*   let ic = Scanning.open_in "IO_in3.txt" in 
  try
    let case = ref 1 in
    while true do 
      bscanf ic "%d %d\n" (fun a b ->
        if !case > 1 then printf "\n";
        printf "Case %d: %d\n" !case (a+b);
        incr case
      )
    done
  with End_of_file ->
    () *)

(*   let ic = Scanning.open_in "IO_in4.txt" in 
  try
    while true do 
      bscanf ic "%d" (fun k ->
        let ans = ref 0 in
        for i = 1 to k do 
          bscanf ic " %d" (fun v -> ans := !ans + v) 
        done;
        bscanf ic "\n" ();
        printf "%d\n" !ans
      )
    done
  with End_of_file ->
    () *)

(*   let ic = Scanning.open_in "IO_in5.txt" in 
  let rec sum_line acc =
    bscanf ic "%d%c" (fun v dummy ->
      if dummy = '\n' then printf "%d\n" (acc+v)
      else sum_line (acc+v)
    )
  in
  try
    while true do 
      sum_line 0
    done
  with End_of_file ->
    () *)
