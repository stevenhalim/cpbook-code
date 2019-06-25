open Printf
open Scanf

let () =
  let a = [| 4; -5; 4; -3; 4; 4; -4; 4; -5 |] in               (* a sample array a *)
  let running_sum = ref 0 in
  let ans = ref 0 in
  a |> Array.iter (fun x ->                                                (* O(n) *)
      if !running_sum + x >= 0 then begin  (* the overall running sum is still +ve *)
        running_sum := !running_sum + x;
        ans := max !ans !running_sum               (* keep the largest RSQ overall *)
      end
      else             (* the overall running sum is -ve, we greedily restart here *)
        running_sum := 0           (* because starting from 0 is better for future *)
    );                            (* iterations than starting from -ve running sum *)
  printf "Max 1D Range Sum = %d\n" !ans                             (* should be 9 *)
