(* Another n-Queen Problem *)
open Scanf
open Printf
open Int64

let ls_one s = s land (-s)
let n = ref 0
let mask = Array.make 32 0

let rec bf row col left_diag right_diag =
  if row = !n then 1L
  else
    let bit = ref ((lnot (mask.(row) lor col lor left_diag lor right_diag)) land ((1 lsl !n) - 1)) in
    let total = ref 0L in
    while !bit > 0 do 
      let t = ls_one !bit in
      total := add !total (bf (row+1) (col lor t) ((left_diag lor t) lsr 1) ((right_diag lor t) lsl 1));
      bit := !bit - t 
    done;
    !total

let () =
  let case = ref 1 in
  let rec solve () =
    scanf "%d" (fun x ->
      n := x;
      if x <> 0 then begin
        scanf "\n" ();
        for i = 0 to x-1 do 
          mask.(i) <- 0;
          scanf "%s\n" (fun str ->
            for j = 0 to x-1 do 
              if String.get str j = '*' then mask.(i) <- mask.(i) lor (1 lsl j)
            done
          )
        done;
        printf "Case %d: %Ld\n" !case (bf 0 0 0 0);
        incr case;
        solve ()
      end
    )
  in
  solve ()
