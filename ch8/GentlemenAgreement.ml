(* Gentlemen Agreement *)

open Scanf
open Printf
open Int64

let maxi = 62
let am = Array.make maxi zero
let p2 = Array.init maxi (fun i -> shift_left one i)
let dpcon = Array.make maxi zero
let num_v = ref 0
let ns = ref 0
let mxs = ref 0

let rec backtracking i used depth =
  if used = sub (shift_left one !num_v) one then begin
    incr ns;
    mxs := max !mxs depth
  end else
    for j = i to !num_v-1 do 
      if logand used p2.(j) = 0L
      then
        backtracking (j+1) (logor used am.(j)) (depth+1)
    done
;;

let solve () =
  scanf "%d %d\n" (fun v e ->
    num_v := v;
    for i = 0 to v-1 do am.(i) <- (shift_left one i) done;
    for i = 1 to e do 
      scanf "%d %d\n" (fun a b ->
        am.(a) <- logor am.(a) (shift_left one b);
        am.(b) <- logor am.(b) (shift_left one a)
      )
    done;
    dpcon.(v) <- 0L;
    for i = v-1 downto 0 do dpcon.(i) <- logor am.(i) dpcon.(i+1) done;
    ns := 0; mxs := 0;
    backtracking 0 0L 0;
    printf "%d\n%d\n" !ns !mxs
  )

let () =
  scanf "%d\n" (fun tc ->
    for case = 1 to tc do solve () done
  )


